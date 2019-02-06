#include <sstream>

// Flash Strings
typedef char __FlashStringHelper;
#define F(X) (X)

class SpyingSerial {
public:
  operator bool() const { return true; }

  void begin(int baud) { log_ << "begin(" << baud << ")\r\n"; }
  void flush() { log_ << "flush()\r\n"; }

  template <typename T> void print(const T &value) { log_ << value; }

  template <typename T> void println(const T &value) {
    log_ << value << "\r\n";
  }

  void clear() { log_.str(""); }
  std::string log() const { return log_.str(); }

private:
  std::stringstream log_;
};

static SpyingSerial Serial;