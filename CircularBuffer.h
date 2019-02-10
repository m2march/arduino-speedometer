/** Circular buffer class */
template <class T>
class CircularBuffer {
    
    public:

        CircularBuffer(int capacity);
        ~CircularBuffer();

        void push(T& x);

        /** Pre: idx < this.capacity */
        const T& get(int idx) const;

        const T& last() const;

    private:
        T* _elems;  
        int _capacity;
        int _size;
        int _offset;

};

template<class T>
CircularBuffer<T>::CircularBuffer(int capacity) :
    _elems(new T[capacity]), _capacity(capacity), _size(0), _offset(0) {};

template<class T>
void CircularBuffer<T>::push(T& x) {
  int pos = (this->_size + this->_offset) % this->_capacity;
  this->_elems[pos] = x; 
  
  if (_size == _capacity) {
    _offset += 1;
    if (_offset == _capacity) {
      _offset = 0;
    }
  } else {
    _size += 1;
  }
}

template<class T>
const T& CircularBuffer<T>::get(int idx) const {
    int pos = (idx + this->_offset) % this->_capacity;
    return this->_elems[idx];
}

template<class T>
const T& CircularBuffer<T>::last() const {
    int pos = (this->_offset + this->_size) % this->_capacity;
    return this->_elems[pos];
}

template<class T>
CircularBuffer<T>::~CircularBuffer() {
    delete this->_elems;
}
