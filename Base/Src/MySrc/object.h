//============================================================================
// 
// �I�u�W�F�N�g�A�w�b�_�[�t�@�C�� [object.h]
// Author : ���c����
// 
//============================================================================

#pragma once

//****************************************************
// ���O���OBJ���`
//****************************************************
namespace OBJ
{
	/* ���̏ꏊ�̓����o�Ɏ�������^�C�v�����p��enum�Ȃǂ̂ݒ�`���Ă��܂� */

	//****************************************************
	// �`��D��x�w��p�̗񋓌^���`
	//****************************************************
	enum class LAYER : unsigned char
	{
		BG = 0,  // �w�i
		DEFAULT, // �ʏ�
		FRONT,   // �O��
		STENCIL, // �X�e���V��
		UI,      // UI
		MAX
	};

	//****************************************************
	// �^�C�v���ʗp�̗񋓌^���`
	//****************************************************
	enum class TYPE : unsigned char
	{
		NONE = 0, // ����
		PLAYER,   // �v���C���[
		MAX
	};
}

//****************************************************
// �I�u�W�F�N�g�N���X���`
//****************************************************
class CObject
{
public:

	//****************************************************
	// special function
	//****************************************************

	// �R���X�g���N�^
	CObject(OBJ::TYPE Type, OBJ::LAYER Layer);

	// �f�X�g���N�^
	virtual ~CObject() = default;

	//****************************************************
	// virtual function
	//****************************************************
	virtual void Update() = 0; // �X�V����
	virtual void Draw()   = 0; // �`�揈��

	//****************************************************
	// inline function
	//****************************************************

	// �^�C�v�̑���p
	inline OBJ::TYPE GetType() const         { return m_Type; }
	inline void      SetType(OBJ::TYPE Type) { m_Type = Type; }

	// �`��D��x�̑���p
	inline OBJ::LAYER GetLayer() const           { return m_Layer; }
	inline void       SetLayer(OBJ::LAYER Layer) { m_Layer = Layer; }

	// ���S�t���O�̐ݒ�
	inline bool GetDeath() const             { return m_bDeath; }
	inline void SetDeath(bool bState = true) { m_bDeath = bState; }

private:

	//****************************************************
	// data
	//****************************************************
	OBJ::TYPE  m_Type;   // �I�u�W�F�N�g�^�C�v
	OBJ::LAYER m_Layer;  // �`��D��x
	bool       m_bDeath; // ���S�t���O
};