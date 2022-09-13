/**
 *  encode.cpp
 * 2022-06-01 K.OHWADA
 */

// liblzma Encoder Decoder
// code to check if it compiles
// becsuse I don't know how to use class

// reference : https://s-yata.hatenadiary.org/entry/20100722/1279762806

#include <iostream>
#include "lzma.h"

/**
 *  class Encoder
 */
class Encoder
{
public:
  Encoder() : out_(NULL), lzma_(), buf_(NULL), buf_size_(0),
    total_in_(0), total_out_(0)
  {
    lzma_stream initial_lzma = LZMA_STREAM_INIT;
    lzma_ = initial_lzma;
  }
  ~Encoder() { close(); }

  bool open(std::ostream *out, uint32_t preset = 6,
    lzma_check check = LZMA_CHECK_CRC64, std::size_t buf_size = 0)
  {
    close();

    if (buf_size == 0)
      buf_size = DEFAULT_BUF_SIZE;
    try
    {
      buf_ = new uint8_t[buf_size];
      buf_size_ = buf_size;
    }
    catch (...)
    {
      return false;
    }

    lzma_ret ret = lzma_easy_encoder(&lzma_, preset, check);
    if (ret != LZMA_OK)
      return false;
    lzma_.next_out = buf_;
    lzma_.avail_out = buf_size_;

    out_ = out;
    return true;
  }

  bool close()
  {
    bool is_ok = true;
    if (out_ != NULL)
    {
      is_ok = finish();
      lzma_end(&lzma_);
    }
    if (buf_ != NULL)
      delete [] buf_;

    out_ = NULL;
    lzma_stream initial_lzma = LZMA_STREAM_INIT;
    lzma_ = initial_lzma;
    buf_ = NULL;
    buf_size_ = 0;
    return is_ok;
  }

  bool write(const void *data, std::size_t size)
  {
    if (out_ == NULL)
      return false;

    lzma_.next_in = static_cast<const uint8_t *>(data);
    lzma_.avail_in = size;

    while (lzma_.avail_in > 0)
    {
      lzma_ret ret = lzma_code(&lzma_, LZMA_RUN);
      if (ret != LZMA_OK)
        return false;

      if (lzma_.avail_out == 0)
      {
        if (!out_->write(reinterpret_cast<const char *>(buf_),
          buf_size_))
          return false;
        lzma_.next_out = buf_;
        lzma_.avail_out = buf_size_;
      }
    }
    return true;
  }

  std::size_t total_in() const
  {
    return out_ != NULL ? lzma_.total_in : total_in_;
  }
  std::size_t total_out() const
  {
    return out_ != NULL ? lzma_.total_out : total_out_;
  }

private:
  std::ostream *out_;
  lzma_stream lzma_;
  uint8_t *buf_;
  std::size_t buf_size_;
  std::size_t total_in_;
  std::size_t total_out_;

  enum { DEFAULT_BUF_SIZE = 4096 };

  bool finish()
  {
    lzma_ret ret = LZMA_OK;
    do
    {
      ret = lzma_code(&lzma_, LZMA_FINISH);
      if (!out_->write(reinterpret_cast<const char *>(buf_),
        buf_size_ - lzma_.avail_out))
        return false;
      lzma_.next_out = buf_;
      lzma_.avail_out = buf_size_;
    } while (ret == LZMA_OK);
    total_in_ = lzma_.total_in;
    total_out_ = lzma_.total_out;
    return ret == LZMA_STREAM_END;
  }

  // Disallows copy.
  Encoder(const Encoder &);
  Encoder &operator=(const Encoder &);
};


/**
 *  class Decoder
 */
class Decoder
{
public:
  Decoder() : in_(NULL), lzma_(), buf_(NULL), buf_size_(0),
    eof_(false), fail_(false), total_in_(0), total_out_(0)
  {
    lzma_stream initial_lzma = LZMA_STREAM_INIT;
    lzma_ = initial_lzma;
  }
  ~Decoder() {}

  bool open(std::istream *in, std::size_t buf_size = 0)
  {
    close();

    if (buf_size == 0)
      buf_size = DEFAULT_BUF_SIZE;
    try
    {
      buf_ = new uint8_t[buf_size];
      buf_size_ = buf_size;
    }
    catch (...)
    {
      return false;
    }

    lzma_ret ret = lzma_stream_decoder(&lzma_,
      lzma_easy_decoder_memusage(9), 0);
    if (ret != LZMA_OK)
      return false;

    in_ = in;
    return true;
  }

  void close()
  {
    if (in_ != NULL)
      lzma_end(&lzma_);
    if (buf_ != NULL)
      delete [] buf_;

    in_ = NULL;
    lzma_stream initial_lzma = LZMA_STREAM_INIT;
    lzma_ = initial_lzma;
    buf_ = NULL;
    buf_size_ = 0;
    eof_ = false;
    fail_ = false;
  }

  std::size_t read(void *buf, std::size_t size)
  {
    if (in_ == NULL || eof_ || fail_)
      return false;

    lzma_.next_out = static_cast<uint8_t *>(buf);
    lzma_.avail_out = size;
    while (lzma_.avail_out > 0)
    {
      if (lzma_.avail_in == 0)
      {
        in_->read(reinterpret_cast<char *>(buf_), buf_size_);
        lzma_.next_in = buf_;
        lzma_.avail_in = in_->gcount();
      }

      if (!*in_)
      {
        lzma_ret ret = lzma_code(&lzma_, LZMA_FINISH);
        if (ret == LZMA_OK)
          continue;
        else
        {
          if (ret == LZMA_STREAM_END)
          {
            total_in_ = lzma_.total_in;
            total_out_ = lzma_.total_out;
            eof_ = true;
          }
          else
            fail_ = true;
          break;
        }
      }
      else
      {
        lzma_ret ret = lzma_code(&lzma_, LZMA_RUN);
        if (ret != LZMA_OK)
        {
          fail_ = true;
          break;
        }
      }
    }
    return size - lzma_.avail_out;
  }

  std::size_t total_in() const
  {
    return in_ != NULL ? lzma_.total_in : total_in_;
  }
  std::size_t total_out() const
  {
    return in_ != NULL ? lzma_.total_out : total_out_;
  }

  bool eof() const { return eof_; }
  bool fail() const { return fail_; }

private:
  std::istream *in_;
  lzma_stream lzma_;
  uint8_t *buf_;
  std::size_t buf_size_;
  bool eof_;
  bool fail_;
  std::size_t total_in_;
  std::size_t total_out_;

  enum { DEFAULT_BUF_SIZE = 4096 };

  // Disallows copy.
  Decoder(const Decoder &);
  Decoder &operator=(const Decoder &);
};


/**
 *  main
 */
int main()
{
  Encoder   encoder;
  Decoder   decoder;

    std::cout << "noting to do" << std::endl;

    return 0;
}

