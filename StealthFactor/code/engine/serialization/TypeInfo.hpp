#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <engine/serialization/Serialize.hpp>

namespace engine
{
	namespace serialization
	{
		class Serializer;

		enum class Type
		{
			UnsignedChar,
			Int,
			Float,
			String,
			Vector,
			Serializable,
			SerializablePtr,
		};

		struct TypeInfo
		{
			Type type;
			void *methods;
		};

		template <typename T>
		struct TypeInfoValue
		{
			static TypeInfo value;
		};


		template <>
		TypeInfo TypeInfoValue<unsigned char>::value = TypeInfo{ Type::UnsignedChar };

		template <>
		TypeInfo TypeInfoValue<int>::value = TypeInfo{ Type::Int };

		template <>
		TypeInfo TypeInfoValue<float>::value = TypeInfo{ Type::Float };

		template <>
		TypeInfo TypeInfoValue<std::string>::value = TypeInfo{ Type::String };


		// Vector

		struct VectorMethods
		{
			virtual const TypeInfo &getItemTypeInfo() const = 0;
			virtual std::size_t getSize(void *vector) const = 0;
			virtual void setSize(void *vector, std::size_t n) const = 0;
			virtual void *getValueAt(void *vector, std::size_t i) const = 0;
		};

		template <typename U>
		struct ImplVectorMethods : VectorMethods
		{
			const TypeInfo &getItemTypeInfo() const override
			{
				return TypeInfoValue<U>::value;
			}

			std::size_t getSize(void *vector) const override
			{
				return reinterpret_cast<std::vector<U> *>(vector)->size();
			}

			void setSize(void *vector, std::size_t n) const override
			{
				reinterpret_cast<std::vector<U> *>(vector)->resize(n);
			}

			void *getValueAt(void *vector, std::size_t i) const override
			{
				return &(*reinterpret_cast<std::vector<U> *>(vector))[i];
			}

			static ImplVectorMethods value;
		};

		template <typename U>
		ImplVectorMethods<U> ImplVectorMethods<U>::value;

		template <typename U>
		struct TypeInfoValue<std::vector<U>>
		{
			static TypeInfo value;
		};

		template <typename U>
		TypeInfo TypeInfoValue<std::vector<U>>::value = TypeInfo{ Type::Vector, &ImplVectorMethods<U>::value };


		// Serializable

		struct SerializableMethods
		{
			virtual void serialize(void *serializable, Serializer &serializer) const = 0;
			virtual void *create() const = 0;
			virtual std::string getClassName() const = 0;
		};

		template <typename T>
		struct ImplSerializableMethods : SerializableMethods
		{
			void serialize(void *serializable, Serializer &serializer) const override
			{
				serialization::serialize(*reinterpret_cast<T *>(serializable), serializer);
			}

			void *create() const override
			{
				assert(false);
				return nullptr;
			}

			std::string getClassName() const override
			{
				return serialization::getClassName<T>();
			}

			static ImplSerializableMethods value;
		};

		template <typename T>
		ImplSerializableMethods<T> ImplSerializableMethods<T>::value;

		template <typename T>
		TypeInfo TypeInfoValue<T>::value = TypeInfo{ Type::Serializable, &ImplSerializableMethods<T>::value };


		// SerializablePtr

		template <typename T>
		struct ImplSerializableMethods<T *> : SerializableMethods
		{
			void serialize(void *serializable, Serializer &serializer) const override
			{
				serialization::serialize(*reinterpret_cast<T *>(*reinterpret_cast<T **>(serializable)), serializer);
			}

			void *create() const override
			{
				return new T;
			}

			std::string getClassName() const override
			{
				return serialization::getClassName<T>();
			}

			static ImplSerializableMethods value;
		};

		template <typename T>
		ImplSerializableMethods<T *> ImplSerializableMethods<T *>::value;

		template <typename T>
		struct TypeInfoValue<T *>
		{
			static TypeInfo value;
		};

		template <typename T>
		TypeInfo TypeInfoValue<T *>::value = TypeInfo{ Type::SerializablePtr, &ImplSerializableMethods<T *>::value };

		template <typename T>
		struct TypeInfoValue<std::unique_ptr<T>>
		{
			static TypeInfo value;
		};

		template <typename T>
		TypeInfo TypeInfoValue<std::unique_ptr<T>>::value = TypeInfo{ Type::SerializablePtr, &ImplSerializableMethods<T *>::value };
	}
}
