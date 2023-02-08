#include"MatrixEffect.h"
#include"Singleton.h"
#include"SpriteDrawer.h"
#include"XMF3Math.h"
#include"Time.h"
MatrixEffect::MatrixEffect(int matSize)
	:m_sprite(Singleton<SpriteDrawer>::GetInstance())
	,m_position(XMFLOAT2(900,0))
	,m_timer(new Time())
	,m_randSize(matSize)
{
			m_spriteMap[0] =  SpriteType::matrix0;
			m_spriteMap[1] =  SpriteType::matrix1;
	RandomSetting();
}

MatrixEffect::~MatrixEffect()
{
	delete m_timer;
}

void MatrixEffect::Update()
{
	m_position.y+=2+randTiming;

	if (m_position.x > 1280)
	{
		if (m_position.y > 900)
		{
			m_effectConcentration -= 0.1f;
			if (m_effectConcentration < 0.1f)
			{
				m_position.y = 0;
				ClearMatrix();
				RandomSetting();
			}
		}
		
	}
	else if (m_position.y > 400)
	{
		m_effectConcentration -= 0.1f;
		if (m_effectConcentration < 0.1f)
		{
			m_position.y = 0;
			ClearMatrix();
			RandomSetting();
		}
	}
	
	m_timer->SetTimer(0.1f);
	if (m_timer->CheakTime())
	{
		for (auto mat : m_drawType)
		{
			//‚O‚©‚P‚©
			bool flag = false;
			if (rand() % 2 == 0)
			{
				flag = !flag;
			}
			mat = flag;
		}
	}
}

void MatrixEffect::Draw()
{
	int i = 0;
	float cons= 1.0f/m_drawType.size();
	for (auto mat: m_drawType)
	{

		if (mat)
		{
			m_sprite.Draw(m_spriteMap[type0], 
				XMFLOAT2(m_position.x, (m_position.y-(i*(MATRIX_SIZE*m_randSize)))), 0.1f*m_randSize,m_sprite.GetColorWithalpha(m_effectConcentration-(cons*i)));
		}
		else
		{
			m_sprite.Draw(m_spriteMap[type1],
				XMFLOAT2(m_position.x, (m_position.y - (i * (MATRIX_SIZE * m_randSize)))), 0.1f * m_randSize,m_sprite.GetColorWithalpha(m_effectConcentration - (cons * i)));
		}
		i++;
	}
	

}

void MatrixEffect::RandomSetting()
{
	int xPos=(rand() %9) +10;
	m_position.x=xPos * 100;
	m_effectConcentration = 1.0f;
	int i = 0;
	int randomNum = 5+rand()%5;

	randTiming = 1+rand()%5;
	for (int i = 0; i < randomNum; i++)
	{
		//‚O‚©‚P‚©
		bool flag = false;
		if (rand() % 2 == 0)
		{
			flag = !flag;
		}

		m_drawType.push_back(flag);
	}
}

void MatrixEffect::ClearMatrix()
{
	m_drawType.clear();
}
