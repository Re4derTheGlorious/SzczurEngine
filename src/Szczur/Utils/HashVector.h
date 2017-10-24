#pragma once

#include <algorithm>
#include <tuple>
#include <vector>

#include <Szczur/Utils/Algorithm.h>

namespace rat {
	template<typename K, typename T>
	class HashVector {
	public:

		using Key_t       = K;
		using Value_t     = T;
		using Pair_t      = std::tuple<Key_t, Value_t>;
		using Container_t = std::vector<Pair_t>;

	private:

		Container_t _container;

	public:

	    HashVector() = default;

	    HashVector(const HashVector&) = default;

	    HashVector& operator = (const HashVector&) = default;

	    HashVector(HashVector&&) = default;

	    HashVector& operator = (HashVector&&) = default;

		void reserve(size_t capacity) {
			_container.reserve(capacity);
		}

		template <typename... Ts>
		Value_t& emplace(Key_t key, Ts&&... args) {
			_container.emplace_back(key, std::forward<Ts>(args)...);
			return std::get<1>(_container.back());
		}

		void clear() {
			_container.clear();
		}

		Value_t& get(Key_t key) {
			return std::get<1>(*interpolationSearch(std::begin(_container), std::end(_container), key, [](const auto& a) {
				return std::get<0>(a);
			}));
		}

		Value_t& operator [] (Key_t key) {
			return get(key);
		}

		const Value_t& get(Key_t key) const {
			return std::get<1>(*interpolationSearch(std::begin(_container), std::end(_container), key, [](const auto& a) {
				return std::get<0>(a);
			}));
		}

		const Value_t& operator [] (Key_t key) const {
			return get(key);
		}

		void sort() {
			std::sort(std::begin(_container), std::end(_container), [](const auto& a, const auto& b) {
				return std::get<0>(a) < std::get<0>(b);
			});
		}

		bool isSorted() const {
			return !isEmpty() && std::is_sorted(std::begin(_container), std::end(_container), [](const auto& a, const auto& b) {
				return std::get<0>(a) < std::get<0>(b);
			});
		}

		const Pair_t* getData() const {
			return _container.data();
		}

		size_t getSize() const {
			return _container.size();
		}

		bool isEmpty() const {
			return getSize() == 0;
		}

		decltype(auto) begin() const {
			return _container.begin();
		}

		decltype(auto) end() const {
			return _container.end();
		}
	};
}
