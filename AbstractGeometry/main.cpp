#include <iostream>
#include<Windows.h>
#include<cmath>
using namespace std;

namespace Geometry
{
	enum Color
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Violet = 0x00FF00FF
	};

	class Shape
	{
		Color color; //Цвет фигуры
	public:
		void set_color(Color color)
		{
			this->color = color;
		}
		Color get_color()const
		{
			return color;
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		Shape(Color color) :color(color) {}
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			for (int i = 0;i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
		}
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона квадрата: " << get_side() << endl;
			Shape::info();
		}
	};
	class Rectangle :public Shape
	{
		double side_1;
		double side_2;
	public:
		void set_side_1(double side_1)
		{
			this->side_1 = side_1;
		}
		void set_side_2(double side_2)
		{
			this->side_2 = side_2;
		}
		double get_side_1()const
		{
			return side_1;
		}
		double get_side_2()const
		{
			return side_2;
		}
		double get_area()const override
		{
			return side_1 * side_2;
		}
		double get_perimeter()const override
		{
			return (side_1 + side_2) * 2;
		}
		void draw()const override
		{
			//cout << "Прямоугольник" << endl;
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd); // Контекст устройства - это то на чем мы будем рисовать 
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
			//PS_SOLID
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, 200, 100, 500, 400);
			// :: - GlobalScope
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc); // контекст устройства занимает ресурсы , которые нужно освободить 
		}

		Rectangle(double side_1, double side_2, Color color) :Shape(color)
		{
			set_side_1(side_1);
			set_side_2(side_2);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1: " << get_side_1() << endl;
			cout << "Сторона 2: " << get_side_2() << endl;
			Shape::info();
		}
		
		
	};
	class Triangle : public Shape
	{
		double side_1;
		double side_2;
		double side_3;
	public:

		void set_side_1(double side_1)
		{
			this->side_1 = side_1;
		}
		void set_side_2(double side_2)
		{
			this->side_2 = side_2;
		}
		void set_side_3(double side_3)
		{
			this->side_3 = side_3;
		}
		double get_side_1()const
		{
			return side_1;
		}
		double get_side_2()const
		{
			return side_2;
		}
		double get_side_3()const
		{
			return side_3;
		}
		double get_perimeter()const override
		{
			return side_1 + side_2 + side_3;
		}
		double get_area()const override
		{
			double p = get_perimeter() / 2;
			return sqrt(p * (p - side_1) * (p - side_2) * (p - side_3));
		}
		void draw()const override
		{
			cout << "Здесь когда-нибудь будет нарисован треугольник";
		}
		Triangle(double side_1, double side_2, double side_3, Color color) :Shape(color)
		{
			set_side_1(side_1);
			set_side_2(side_2);
			set_side_3(side_3);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1: " << get_side_1() << endl;
			cout << "Сторона 2: " << get_side_2() << endl;
			cout << "Сторона 3: " << get_side_3() << endl;
			Shape::info();
		}
	};
}


void main()
{
	setlocale(LC_ALL,"");
	Geometry::Square square(5, Geometry::Color::Red);
	square.info();
	Geometry::Rectangle rectangle(20, 15, Geometry::Color::Blue);
	rectangle.info();
	Geometry::Triangle triangle(20, 15,15 , Geometry::Color::Blue);
	triangle.info();
}