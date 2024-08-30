#include "SpaceGame.h"
#include "Engine.h"

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);
    rapidjson::Document document;
    Json::Load("Scenes/title.json", document);
    m_scene->Read(document);

	m_scene->Initialize();

	ADD_OBSERVER(PlayerDead, SpaceGame::OnPlayerDead);
	ADD_OBSERVER(AddPoints, SpaceGame::OnAddPoints);

    return false;
}

void SpaceGame::Shutdown()
{
	m_scene->RemoveAll(true);
}

void SpaceGame::Update(float dt)
{
    switch (m_state)
    {
    case eState::Title:
        stateTimer -= dt;
        if (stateTimer <= 0) {
            if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
            {
                m_scene->RemoveAll(true);

                rapidjson::Document document;
                Json::Load("Scenes/scene.json", document);
                m_scene->Read(document);
                m_scene->Initialize();

                stateTimer = 1;
                enemySpawnCount = 3;
                m_state = eState::Game;
            }
        }
        break;

    case eState::Game:
        if (m_scene->GetActor<Actor>("player") == nullptr) {
            m_scene->RemoveAll(true);

            rapidjson::Document document;
            Json::Load("Scenes/gameover.json", document);
            m_scene->Read(document);
            m_scene->Initialize();

            m_state = eState::GameOver;
        }

        

        spawnTimer--;
        
        if (spawnTimer <= 0) {
            if (waveNum % 3 == 0 && waveNum != 0) enemySpawnCount++;
            for (int i = 0; i < enemySpawnCount; i++) {
                auto enemy = Factory::Instance().Create<Actor>("enemy");
                enemy->transform.position = { randomf((float)50, (float)m_scene->engine->GetRenderer().GetWidth() - 50), 0.0f };
                m_scene->AddActor(std::move(enemy), true);
            }
            waveNum++;
            spawnTimer = 6000;
        }
        break;

    case eState::GameOver:
        
        stateTimer -= dt;
        if (stateTimer <= 0)
        {
            if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
            {
                m_scene->RemoveAll(true);

                rapidjson::Document document;
                Json::Load("Scenes/title.json", document);
                m_scene->Read(document);
                m_scene->Initialize();

                stateTimer = 1;
                m_state = eState::Title;
            }
        }
        
        break;
    default:
        break;
    }

    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
    m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDead(const Event& event)
{
	
}

void SpaceGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}
