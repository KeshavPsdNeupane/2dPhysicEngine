#include "Utility.h"


sf::Vector2f BasicKinematic::Distance(const sf::Vector2f& u, const sf::Vector2f& a, const float& t){
     return (u + (1.0f / 2.0f) * a * t) * t;
}

sf::Vector2f BasicKinematic::Distance(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& a) {
    float S_x = (a.x != 0) ? (v.x * v.x - u.x * u.x) / (2 * a.x) : 0.0f;
    float S_y = (a.y != 0) ? (v.y * v.y - u.y * u.y) / (2 * a.y) : 0.0f;
    if (u.x - v.x > 0) {S_x = -std::abs(S_x);  }
    else {S_x = std::abs(S_x);}

    if (u.y - v.y > 0) { S_y = -std::abs(S_y); }
    else {S_y = std::abs(S_y);  }
    return { S_x, S_y };
}




float BasicKinematic::GetTime(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& a) {
    float magnitude_a = VectorOperation::Magnitude(a);
    if (magnitude_a == 0) { std::cout<<"division by zero on GetTime1 ,a " << std::endl; return 0; }
    return VectorOperation::Magnitude(v-u) / magnitude_a;
}

float BasicKinematic::GetTime2(const sf::Vector2f& u, const sf::Vector2f& a, const sf::Vector2f& s) {
    float u_dot_u = DotProduct(u, u);
    float a_dot_s = DotProduct(a, s);
    float magnitude_a = Magnitude(a);
    if (magnitude_a == 0) { std::cout << "division by zero on GetTime2 ,a" << std::endl; return 0; }
    float discriminant = u_dot_u + 2 * a_dot_s;
    if (discriminant < 0) { std::cout<< "Discriminiant zero in getTim2 " << std::endl; return 0; }
    float root = std::sqrt(discriminant);
    return (root - Magnitude(u)) / magnitude_a;
}
sf::Vector2f BasicKinematic::FinalVelocity1(const sf::Vector2f& u, const sf::Vector2f& a, const float& t)
{ return u + a * t;}

sf::Vector2f BasicKinematic::FinalVelocity2(const sf::Vector2f& u, const sf::Vector2f& a, const sf::Vector2f& s){
    float time = GetTime(u, a, s);
    return FinalVelocity1(u, a, time);
}
