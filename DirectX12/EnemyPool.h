#pragma once

#include<vector>
#include<unordered_map>
enum class EnemyType;
class EnemyPool
{
public:
	EnemyPool();
	~EnemyPool();
	/// <summary>
	///�@�v�[�����疢�g�p�̃G�l�~�[�N���X���Q�b�g����
	/// </summary>
	class EnemyBase* UnUsedEnemyAdvent(const EnemyType _type);

	/// <summary>
	/// �R���W�����}�l�[�W���[�ɃG�l�~�[�v�[���̓����蔻���o�^����
	/// </summary>
	/// <param name="_mng">
	/// �R���W�����}�l�[�W���[
	/// </param>
	void AddCollision( class CollisionManager* _mng);

	/// <summary>
	/// �R���W�����}�l�[�W���[�̃G�l�~�[�v�[���̓����蔻����폜����
	/// </summary>
	/// <param name="_mng">
	/// �R���W�����}�l�[�W���[
	/// </param>
	void DeleteCollision(class CollisionManager* _mng);

	/// <summary>
	/// �v�[���쐬
	/// </summary>
	void CreateAll();

	/// <summary>
	/// �v�[�����폜
	/// </summary>
	void DestroyAll();
private:
	/// <summary>
	/// �w��̃G�l�~�[�N���X���쐬
	/// </summary>
	/// <param name="_type">
	/// �w�肷��^�C�v
	/// </param>
	void Create(const EnemyType _type);

	/// <summary>
	/// �v�[���{��
	/// </summary>
	std::unordered_map<EnemyType, std::vector<EnemyBase*>> m_enemyPool;

	/// <summary>
	///�@�㋉�{�X�^�C�v���Ƃ̍ő吔
	/// </summary>
	const int HIGHER_ENEMY_MAX = 10;
	
	/// <summary>
	/// ���ʃG�l�~�[�̍ő吔
	/// </summary>
	const int LESSER_ENEMY_MAX = 300;
};
