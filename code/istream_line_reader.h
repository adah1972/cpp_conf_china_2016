#ifndef ISTREAM_LINE_READER_H
#define ISTREAM_LINE_READER_H

#include <cassert>                  // assert
#include <istream>                  // std::istream
#include <string>                   // std::string

class istream_line_reader {
public:
    class iterator {  // implements InputIterator
    public:
        typedef const std::string& reference;
        typedef std::string value_type;

        iterator() : stream_(NULL) {}
        explicit iterator(std::istream& is) : stream_(&is)
        {
            ++*this;
        }

        reference operator*()
        {
            assert(stream_ != NULL);
            return line_;
        }
        value_type* operator->()
        {
            assert(stream_ != NULL);
            return &line_;
        }
        iterator& operator++()
        {
            getline(*stream_, line_);
            if (!*stream_) {
                stream_ = NULL;
            }
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            ++*this;
            return temp;
        }

        bool operator==(const iterator& rhs) const
        {
            return stream_ == rhs.stream_;
        }
        bool operator!=(const iterator& rhs) const
        {
            return !operator==(rhs);
        }

    private:
        std::istream* stream_;
        std::string line_;
    };

    explicit istream_line_reader(std::istream& is)
        : stream_(is)
    {
    }
    iterator begin()
    {
        return iterator(stream_);
    }
    iterator end() const
    {
        return iterator();
    }

private:
    std::istream& stream_;
};

#endif // ISTREAM_LINE_READER_H
