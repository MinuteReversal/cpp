class Circle
{
public:
  explicit Circle(double r) : R(r) {}
  explicit Circle(int x, int y = 0) : X(x), Y(y) {}
  explicit Circle(const Circle &c) : R(c.R), X(c.X), Y(c.Y) {}

private:
  double R;
  int X;
  int Y;
};

int main(int argc, char *argv[])
{
  //一下3句，都会报错
  //Circle A = 1.23;
  //Circle B = 123;
  //Circle C = A;

  //只能用显示的方式调用了
  //未给拷贝构造函数加explicit之前可以这样
  // Circle A = Circle(1.23);
  // Circle B = Circle(123);
  // Circle C = A;

  //给拷贝构造函数加了explicit后只能这样了
  Circle A(1.23);
  Circle B(123);
  Circle C(A);
  return 0;
}