#pragma once

#include "Audio.h"
#include "CameraController.h"
#include "DeathBlock.h"
#include "DeathParticles.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Goal.h"
#include "JumpBlock.h"
#include "Input.h"
#include "MapChipField.h"
#include "Model.h"
#include "OverScene.h"
#include "Player.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>
#include <vector>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsDead() const { return isDead_; };
	bool IsFinished() const { return finished_; };

private: // メンバ変数
	enum class Phase {
		kPlay,  // ゲームプレイ
		kDead, // デス演出
		kGoal,  // ゲームクリア
	};

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 自キャラ
	Player* player_ = nullptr;
	// モデルデータ
	Model* modelPlayer_ = nullptr;
	Model* modelBlock_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelGoal_ = nullptr;
	Model* modelDeathBlock_ = nullptr;
	Model* modelJumpBlock_ = nullptr;
	Model* modelDeathParticle_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	WorldTransform worldTransformSkydome_;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// マップチップフィールド
	MapChipField* mapChipField_;
	CameraController* cameraController = nullptr;

	std::list<DeathBlock*> deathBlocks_;
	std::list<Goal*> goals_;
	std::list<JumpBlock*> jumpBlocks_;

	bool finished_ = false;
	bool isDead_ = false;
	Phase phase_;

	DeathParticles* deathParticles_ = nullptr;

	void ChangePhase();

	void GenerateBlocks();

	void UpdateCamera();

	void UpdateBlocks();

	// 衝突判定と応答

	void CheckAllCollisions();
};