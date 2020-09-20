#include "stdafx.h"
#include "SceneManager.h"


void SceneManager::Destroy()
{
	for (Scene* iter : Manager)
	{
		delete iter;
	}
	
	Manager.clear();
}

void SceneManager::NextScene()
{
	switch (CurrentScene->GetType())
	{
	case TITLE:
		{
			if (ID.empty()) ID = CurrentScene->GetID();
			LobbyScene* Lobby = new LobbyScene;
			Lobby->InitScene(FrontBuffer, BackBuffer);
			Manager.push_back(Lobby);
			CurrentScene = Manager[LOBBY];
			CurrentScene->SetID(ID);
		}
		break;
	case LOBBY:
		{
			GameScene* InGame = new GameScene(PlayerFlag, CharFlag);
			InGame->InitScene(FrontBuffer, BackBuffer);
			Manager.push_back(InGame);
			CurrentScene = Manager[GAME];
			CurrentScene->SetType(GAME);
			CurrentScene->SetID(ID);
		}
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

void SceneManager::InitManager(HDC* Front, HDC* Back)
{
	Scene* Title = new TitleScene;
	Title->InitScene(Front, Back);

	Manager.push_back(Title);

	CurrentScene = Manager[TITLE];
	FrontBuffer = Front;
	BackBuffer = Back;
}
