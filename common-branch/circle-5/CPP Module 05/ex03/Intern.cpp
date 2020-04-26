#include "Intern.hpp"


Form *Intern::createRobotomy(std::string const &target)
{
    return new RobotomyRequestForm(target);
};

Form *Intern::createShruberry(std::string const &target)
{
        return new ShrubberyCreationForm(target);
};

Form *Intern::createPresidential(std::string const &target)
{
        return new PresidentialPardonForm(target);
};

const int Intern::form_nbr = 3;

const Intern::t_forms Intern::forms[Intern::form_nbr] = {
    {"robotomy request", Intern::createRobotomy},
    {"shruberry creation", Intern::createShruberry},
    {"presidential pardon", Intern::createPresidential},
};

Intern::Intern(void)
{

};

Intern::Intern(const Intern &src)
{
    *this = src;
};

Intern::~Intern()
{

};

Intern &Intern::operator= (const Intern &rhs)
{
    (void)rhs;
    return (*this);
};

Form    *Intern::makeForm(std::string const &form, std::string const &target) {
    bool found;

    found = false;
    for (int i = 0; i < this->form_nbr ; i++)
        if (this->forms[i].name == form)
        {
            std::cout << "Intern creates " + form << std::endl;
            return (this->forms[i].new_form(target));
            found = true;
        }

    std::cout << "Form name is not valid." << std::endl;
    return NULL;
}
