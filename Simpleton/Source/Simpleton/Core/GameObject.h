//====================================================================================================
// Filename:	GameObject.h
// Created by:	Johnny Wu
// Description:	Class for a GameObject.
//====================================================================================================
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <string>
#include <typeinfo>
#include <unordered_map>

#include "Transform.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void HandleCollision(GameObject* other) = 0;
	virtual void Deactivate() = 0;
	
	//====================================================================================================
	// Inline Definition
	//====================================================================================================
	template <typename T>	T* AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Type is not derived from Component");

		if(mComponents.count(&typeid(T)) != 0)
		{
			printf("Cannot add more than one of the same component");
			return nullptr;
		}

		T* newComponent = new T();
		newComponent->gameObject = this;
		newComponent->enabled = mActive;
		mComponents[&typeid(*newComponent)] = newComponent;
		return newComponent;
	}
	
	template <typename T>	T* GetComponent()
	{
		if(mComponents[&typeid(T)] != nullptr)
			return static_cast<T*>(mComponents[&typeid(T)]);
		else
			return nullptr;
	}

	// Getters and Setters
	bool IsActive() const				{ return mActive; }
	void SetActive(bool a);

	// Public variables
	std::string name;
	int layer;
	Transform* transform;

protected:
	void UpdateComponents();

private:	
	bool mActive;
	std::unordered_map<const std::type_info*, Component*> mComponents;
};

#endif // #ifndef _GAMEOBJECT_H_