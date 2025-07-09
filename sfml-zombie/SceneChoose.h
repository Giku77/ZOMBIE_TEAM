#pragma once
#include "Scene.h"
class SceneChoose :
    public Scene
{
protected:

public:
	SceneChoose();
	~SceneChoose() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

