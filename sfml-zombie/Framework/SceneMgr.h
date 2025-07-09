#pragma once
class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	enum class Type { A, B, C, D, E, F };

	Type type = Type::A;

	SceneMgr() = default;
	~SceneMgr() = default;

	std::unordered_map<SceneIds, Scene*> scenes;

	SceneIds startScene = SceneIds::Title;
	SceneIds currentScene = SceneIds::None;
	SceneIds nextScene = SceneIds::None;

public:
	void Init();
	void Release();

	Scene* GetCurrentScene() { return scenes[currentScene]; }
	SceneIds GetCurrentSceneId() const { return currentScene; }
	void ChangeScene(SceneIds id);
	void setType(int i) { type = (Type)i; }
	Type getType() const { return type; }

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

#define SCENE_MGR (SceneMgr::Instance())

