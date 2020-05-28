#include "Fps.h"
#include "FpsGame.h"
#include "Vector3.h"
#include "Matrix.h"
#include <iostream>
#include <memory>
using namespace std;

int main()
{
    auto game = std::make_shared<FpsGame>();
    game->RunGame();
    return 0;
}

/*TODO: also add sprite and texture classes!
    auto a = Vector3(1, 0, 0);//2, 3);
    auto b = Vector3(0, 1, 0);//2, 3, 4);
    cout << a.ToString() << "+" << b.ToString() << "=" << (a+b).ToString() << endl;
    cout << a.ToString() << "-" << b.ToString() << "=" << (a-b).ToString() << endl;
    cout << "-" << a.ToString() << "=" << (-a).ToString() << endl;
    cout << a.ToString() << "*" << 5 << "=" << (a*5).ToString() << endl;
    cout << a.ToString() << " dot " << b.ToString() << "=" << a.DotProduct(b) << endl;
    cout << a.ToString() << " cross " << b.ToString() << "=" << (a.CrossProduct(b)).ToString() << endl;
    cout << a.ToString() << " length " << "=" << a.Length() << endl;
    cout << a.ToString() << " normal " << "=" << a.Normal().ToString() << endl;

    auto m = Matrix();
    cout << "Identity matrix: " << m.ToString() << endl;
    auto m2 = Matrix(m);
    m2 = m.Scale(Vector3(2, 2, 2));
    cout << "Scaled matrix: " << m2.ToString() << endl;
    cout << "matrix * vector: " << (m2*a).ToString() << endl;
    cout << "matrix * matrix: " << (m*m2).ToString() << endl;
    cout << "matrix rotation: " << (m.RotateZ(45)).ToString() << endl;
    */
