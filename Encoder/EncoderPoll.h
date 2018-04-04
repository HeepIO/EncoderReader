#define ENCODER_POS_0 0b00
#define ENCODER_POS_1 0b01
#define ENCODER_POS_2 0b11
#define ENCODER_POS_3 0b10

class EncoderPoll{
public:
	enum CountMode {Quad4X, Quad2X, Quad1X};

	EncoderPoll(int _aPin, int _bPin, CountMode _mode = Quad4X);

	EncoderPoll(int _aPin, int _bPin, int _highValue, int _lowValue, CountMode _mode = Quad4X, int startValue = 0);

	void RunEncoder();

	int ReadEncoder();

private:
	int currentPosition;
	int lastEncoderVal;
	CountMode mode;
	int aPin;
	int bPin;

	int highValue;
	int lowValue;

	bool constrainRange;
};