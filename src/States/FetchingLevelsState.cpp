#include "FetchingLevelsState.h"
#include "StateManager.h"


FetchingLevelsState::FetchingLevelsState(StateManager *stateManager) :
        BaseState(stateManager),
        m_local_levels_file(true, tinyxml2::COLLAPSE_WHITESPACE),
        m_remote_levels_file(true, tinyxml2::COLLAPSE_WHITESPACE) {}

void FetchingLevelsState::onCreate() {
    loadAndFetchLevels();

    //
    m_stateManager->getContext()->m_level_manager->loadLevels();

    m_stateManager->remove(StateType::FetchingLevels);
    m_stateManager->switchTo(StateType::MainMenu);
}

void FetchingLevelsState::loadAndFetchLevels() {
    loadRemoteLevelsFile();

    auto is_local_file_valid = m_stateManager->getContext()->m_level_manager->checkLevels();

    if (!is_local_file_valid && m_remote_content.empty())
        throw NoLevelsFileException();

    if (m_remote_content.empty())
        return;

    auto is_remote_file_parsing_succeeded = parseRemoteLevelsFile();

    if (!is_remote_file_parsing_succeeded)
        return;

    if (is_local_file_valid)
        mergeLevelPassedAttributes();

    saveRemoteLevelsToLocalFile();
}

void FetchingLevelsState::loadRemoteLevelsFile() {
    struct Content {
        std::string data;

        static size_t Write(char *data, size_t size, size_t nmemb, void *p) {
            return static_cast<Content *>(p)->WriteImpl(data, size, nmemb);
        }

        size_t WriteImpl(char *ptr, size_t size, size_t nmemb) {
            data.insert(end(data), ptr, ptr + size * nmemb);
            return size * nmemb;
        }
    };

    Content content;

    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Content::Write);
    curl_easy_setopt(curl, CURLOPT_URL, Constants::Paths::levels_hostname);

    if (curl_easy_perform(curl) != CURLE_OK)
        return;

    m_remote_content = std::move(content.data);
    m_remote_content.push_back('\0');
}

bool FetchingLevelsState::parseRemoteLevelsFile() {
    auto result = m_remote_levels_file.Parse(m_remote_content.c_str());

    return result == tinyxml2::XML_SUCCESS;
}

void FetchingLevelsState::mergeLevelPassedAttributes() {
    auto level_manager = m_stateManager->getContext()->m_level_manager;
    auto levels_filename = level_manager->getLevelsFilename();


    m_local_levels_file.LoadFile(levels_filename);

    auto level_node = m_local_levels_file.FirstChildElement("levels")->FirstChildElement("level");
    std::map<int, bool> levels_progress;

    for (; level_node != nullptr; level_node = level_node->NextSiblingElement("level")) {
        levels_progress[level_node->IntAttribute("id")] = level_node->BoolAttribute("passed");
    }

    level_node = m_remote_levels_file.FirstChildElement("levels")->FirstChildElement("level");
    for (; level_node != nullptr; level_node = level_node->NextSiblingElement("level")) {
        int level_id = level_node->IntAttribute("id");

        if (levels_progress.contains(level_id)) {
            level_node->SetAttribute("passed", levels_progress[level_id]);
        }
    }
}

void FetchingLevelsState::saveRemoteLevelsToLocalFile() {
    std::cout << m_remote_levels_file.ToText() << std::endl;

    m_remote_levels_file.SaveFile(m_stateManager->getContext()->m_level_manager->getLevelsFilename());
}

void FetchingLevelsState::onDestroy() {

}

void FetchingLevelsState::activate() {

}

void FetchingLevelsState::deactivate() {

}

void FetchingLevelsState::update(const sf::Time &time) {

}

void FetchingLevelsState::draw() {

}
