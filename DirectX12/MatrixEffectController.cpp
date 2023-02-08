#include"MatrixEffectController.h"
#include"MatrixEffect.h"
MatrixEffectController::MatrixEffectController()
{
	m_matrixEffectVec.push_back(new MatrixEffect(1));
	m_matrixEffectVec.push_back(new MatrixEffect(1));
	m_matrixEffectVec.push_back(new MatrixEffect(1));

	m_matrixEffectVec.push_back(new MatrixEffect(1));
	m_matrixEffectVec.push_back(new MatrixEffect(1));
	m_matrixEffectVec.push_back(new MatrixEffect(1));
	m_matrixEffectVec.push_back(new MatrixEffect(2));
	m_matrixEffectVec.push_back(new MatrixEffect(2));
	m_matrixEffectVec.push_back(new MatrixEffect(3));

	m_matrixEffectVec.push_back(new MatrixEffect(2));
	m_matrixEffectVec.push_back(new MatrixEffect(2));
	m_matrixEffectVec.push_back(new MatrixEffect(3));
}

MatrixEffectController::~MatrixEffectController()
{
	for (auto itr : m_matrixEffectVec)
	{
		if (itr)
		{
			delete itr;
		}
	}
	m_matrixEffectVec.clear();
	m_matrixEffectVec.shrink_to_fit();
}

void MatrixEffectController::Update()
{
	for (auto itr : m_matrixEffectVec)
	{
		itr->Update();
	}
	
}

void MatrixEffectController::Draw()
{
	for (auto itr : m_matrixEffectVec)
	{
		itr->Draw();
	}
}
