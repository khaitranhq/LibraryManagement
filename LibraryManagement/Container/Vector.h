#pragma once

template<typename Ty>
class vector
{
public:
	using iterator = Ty*;
	using const_iterator = const Ty*;

	vector();
	explicit vector(const size_t count);
	vector(const size_t count, const Ty& val);
	vector(const vector& other);
	vector(vector&& other);
	~vector();

	vector& operator=(const vector& other);
	vector& operator=(vector&& other);

	size_t size() const;
	size_t capacity() const;

	void push_back(const Ty& val);
	void push_back(Ty&& val);
	void pop_back();
	void erase(const int&);

	Ty& front();
	const Ty& front() const;
	Ty& back();
	const Ty& back() const;
	Ty& operator[](const size_t pos);
	const Ty& operator[](const size_t pos) const;

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
private:
	Ty* buffer;
	iterator m_first;
	iterator m_last;
	iterator m_end;

	void realloc(const size_t factor, const size_t carry);
	void alloc(const size_t cap);
};

template<typename Ty>
vector<Ty>::vector() : buffer(new Ty[10]), m_first(buffer), m_last(buffer), m_end(buffer + 10) {

}

template<typename Ty>
vector<Ty>::vector(const size_t count) : buffer(new Ty[count]), m_first(buffer), m_last(buffer + count), m_end(buffer + count) {

}

template<typename Ty>
vector<Ty>::vector(const size_t count, const Ty& val) : buffer(new Ty[count]), m_first(buffer), m_last(buffer + count), m_end(buffer + count) {
	int cnt = count;
	while (cnt--) {
		buffer[cnt] = val;
	}
}

template<typename Ty>
vector<Ty>::vector(const vector& other) : buffer(new Ty[other.capacity()]), m_first(buffer), m_last(buffer + other.size()), m_end(buffer + other.capacity()) {
	for (size_t i = 0; i < size(); ++i) {
		buffer[i] = other[i];
	}
}

template<typename Ty>
vector<Ty>::vector(vector&& other) : buffer(other.buffer), m_first(other.m_first), m_last(other.m_last), m_end(other.m_end) {
	other.buffer = nullptr;
	other.m_first = other.m_last = other.m_end = nullptr;
}

template<typename Ty>
vector<Ty>::~vector() {
	if (buffer != nullptr) {
		m_first = m_last = m_end = nullptr;
		delete[] buffer;
	}
}

template<typename Ty>
vector<Ty>& vector<Ty>::operator=(const vector<Ty>& other) {
	if (this == &other) {
		return *this;
	}
	this->~vector();
	buffer = new Ty[other.capacity()];
	m_first = buffer;
	m_last = buffer + other.size();
	m_end = buffer + other.capacity();
	for (size_t i = 0; i < size(); ++i) {
		buffer[i] = other[i];
	}
	return *this;
}

template<typename Ty>
vector<Ty>& vector<Ty>::operator=(vector<Ty>&& other) {
	if (this == &other) {
		return *this;
	}
	this->~vector();

	buffer = other.buffer;
	m_first = other.m_first;
	m_last = other.m_last;
	m_end = other.m_end;

	other.buffer = nullptr;
	other.m_first = other.m_last = other.m_end = nullptr;
	return *this;
}

template<typename Ty>
size_t vector<Ty>::size() const {
	return static_cast<size_t>(m_last - m_first);
}

template<typename Ty>
size_t vector<Ty>::capacity() const {
	return static_cast<size_t>(m_end - m_first);
}

template<typename Ty>
void vector<Ty>::push_back(const Ty& val) {
	if (size() < capacity()) {
		*(m_last++) = val;
		return;
	}
	realloc(2, 2);
	*(m_last++) = val;
}

template<typename Ty>
void vector<Ty>::push_back(Ty&& val) {
	if (size() < capacity()) {
		*(m_last++) = std::move(val);
		return;
	}
	realloc(2, 2);
	*(m_last++) = std::move(val);
}

template<typename Ty>
void vector<Ty>::pop_back() {
	if (size() == 0) {
		throw std::exception("vector is empty");
	}
	(--m_last)->~Ty();
}

template<typename Ty>
void vector<Ty>::erase(const int& index) {
	size_t sz = size();
	for (size_t i = index; i < sz; ++i) {
		buffer[i] = buffer[i + 1];
	}
	--m_last;
}

template<typename Ty>
Ty& vector<Ty>::front() {
	if (size() == 0) {
		throw std::exception("front(): vector is empty");
	}
	return *begin();
}

template<typename Ty>
const Ty& vector<Ty>::front() const {
	if (size() == 0) {
		throw std::exception("front(): vector is empty");
	}
	return *begin();
}

template<typename Ty>
Ty& vector<Ty>::back() {
	if (size() == 0) {
		throw std::exception("back(): vector is empty");
	}
	return *(end() - 1);
}

template<typename Ty>
const Ty& vector<Ty>::back() const {
	if (size() == 0) {
		throw std::exception("back(): vector is empty");
	}
	return *(end() - 1);
}

template<typename Ty>
Ty& vector<Ty>::operator[](const size_t pos) {
	if (pos >= size()) {
		throw std::exception("index out of range");
	}
	return buffer[pos];
}

template<typename Ty>
const Ty& vector<Ty>::operator[](const size_t pos) const {
	if (pos >= size()) {
		throw std::exception("index out of range");
	}
	return buffer[pos];
}

template<typename Ty>
typename vector<Ty>::iterator vector<Ty>::begin() {
	return m_first;
}

template<typename Ty>
typename vector<Ty>::iterator vector<Ty>::end() {
	return m_last;
}

template<typename Ty>
typename vector<Ty>::const_iterator vector<Ty>::begin() const {
	return m_first;
}

template<typename Ty>
typename vector<Ty>::const_iterator vector<Ty>::end() const {
	return m_last;
}

template<typename Ty>
void vector<Ty>::realloc(const size_t factor, const size_t carry) {
	alloc(capacity() * factor + carry);
}

template<typename Ty>
void vector<Ty>::alloc(const size_t cap) {
	Ty* new_buffer = new Ty[cap];
	size_t sz = size();
	for (size_t i = 0; i < sz; ++i) {
		new_buffer[i] = buffer[i];
	}
	this->~vector();
	buffer = new_buffer;
	m_first = buffer;
	m_last = buffer + sz;
	m_end = buffer + cap;
}
