
enum class TestEnum : short
{
	A,
	B,
	C
};

class ReturnConstEnum
{
private:
	/* data */
public:
	ReturnConstEnum();
	TestEnum Fn() const;
	~ReturnConstEnum();
};
