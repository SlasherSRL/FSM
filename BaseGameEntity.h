#pragma once
class BaseGameEntity
{

private:
	int ID;

	static int nextEligibleID;

public:

	BaseGameEntity(int id);

	void SetID(int id);

	virtual ~BaseGameEntity();

	virtual void Update() = 0;

	int GetID()const;

};

