#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

struct StudentGrade
{
    std::string name{};
    char grade{};
};

class GradeMap
{
    std::vector<StudentGrade> m_map{};

public:
    char& operator[](std::string_view name)
    {
        const auto found{std::find_if(m_map.begin(), m_map.end(), 
                        [name](const StudentGrade& student)
                        {return name == student.name;}
        )};

        if (found != m_map.end())
        {
            return found->grade;
        } else
        {
            m_map.push_back(StudentGrade{static_cast<std::string>(name), 'A'});
            return m_map.back().grade;
        }
    }
};

int main()
{
	GradeMap grades{};

	grades["Joe"] = 'A';
	grades["Frank"] = 'B';

	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

	return 0;
}
