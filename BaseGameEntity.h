#pragma once
class BaseGameEntity
{

private:	
	int ID;
	static int nextValidID;
public:
	BaseGameEntity(int id)
	{
		SetID(id);
	}

	
	virtual  ~BaseGameEntity()
	{

	}
	void SetID(int id)
	{
		ID = id;
	}

	virtual void Update() = 0;
	int GetID()const
	{
		return ID;
	}

};

