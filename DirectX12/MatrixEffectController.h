#pragma once
#include<vector>
class MatrixEffectController
{
public:
	MatrixEffectController();
	~MatrixEffectController();
	void Update();
	void Draw();

	void RandomSetting();

private:
	std::vector<class MatrixEffect* > m_matrixEffectVec;


};
