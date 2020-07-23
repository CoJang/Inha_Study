#include "stdafx.h"
#include "SceneManager.h"


void SceneManager::Destroy()
{
	for (Scene* iter : Manager)
	{
		delete iter;
	}
}

void SceneManager::NextScene()
{
	switch (CurrentScene->GetType())
	{
	case TITLE:
		if (ID.empty()) ID = CurrentScene->GetID();
		CurrentScene = Manager[GAME];
		CurrentScene->SetID(ID);
		break;
	case GAME:
		CurrentScene = Manager[GAMEOVER];
		CurrentScene->SetType(GAMEOVER);
		CurrentScene->SetID(ID);
		break;
	case GAMEOVER:
		CurrentScene = Manager[TITLE];
		CurrentScene->SetType(TITLE);
		CurrentScene->SetID(ID);
		break;
	}

}

void SceneManager::PrevScene()
{
	switch (CurrentScene->GetType())
	{
	case TITLE:
		return;
	case GAME:
		CurrentScene = Manager[TITLE];
		CurrentScene->SetType(TITLE);
		CurrentScene->SetID(ID);
		break;
	case GAMEOVER:
		CurrentScene = Manager[GAME];
		CurrentScene->SetType(GAME);
		CurrentScene->SetID(ID);
		break;
	}
}

void SceneManager::InitManager(HDC* device)
{
	Scene* Title = new TitleScene;
	Scene* InGame = new GameScene;
	Scene* End = new GameOverScene;

	Title->InitScene(device);
	InGame->InitScene(device);
	End->InitScene(device);

	Manager.push_back(Title);
	Manager.push_back(InGame);
	Manager.push_back(End);

	CurrentScene = Manager[TITLE];
	hdc = device;
}
