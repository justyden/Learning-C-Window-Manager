#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Screen {

    friend class Window_Manager;

    public:
        // Types of the class
        using pos = string::size_type;

        // Constructors
        Screen() = default;
        Screen(pos entry_input1, pos entry_input2, char entry_input3);

        // Methods
        Screen &display(std::ostream &entry_display);
        const Screen &display(std::ostream &entry_display) const;
        Screen &set(char entry_set1);
        Screen &set(pos entry_set1, pos entry_set2, char entry_set3);
        char const get() {
            return contents[cursor];
        }
        inline const char get(pos entry_get1, pos entry_get2);
        Screen &move(pos entry_move1, pos entry_move2);

    private:
        void do_display(std::ostream &entry_do) const {
            entry_do << contents;
        }
        pos cursor = 0;
        pos height = 0, width = 0;
        string contents;

};

// Constructor definitions
Screen::Screen(pos entry_input1, pos entry_input2, char entry_input3) {
    height = entry_input1;
    width = entry_input2;
    contents = (entry_input1 * entry_input2, entry_input3);
}

// Method definitons
Screen &Screen::display(std::ostream &entry_display) {
    do_display(entry_display);
    return *this;
}
const Screen &Screen::display(std::ostream &entry_display) const {
    do_display(entry_display); 
    return *this;
}
inline Screen &Screen::set(char entry_set1) {
    contents[cursor] = entry_set1;
    return *this;
}
inline Screen &Screen::set(pos entry_set1, pos entry_set2, char entry_set3) {
    contents[entry_set1 * width + entry_set2] = entry_set3;
    return *this;
}
inline Screen &Screen::move(pos entry_move1, pos entry_move2) {
    pos row = entry_move1 * width;
    cursor = row + entry_move2;
    return *this;
}
char const Screen::get(pos entry_get1, pos entry_get2) {
    pos row = entry_get1 * width;
    return contents[row + entry_get2];
}

class Window_Manager {

    public:
        using ScreenIndex = vector<Screen>::size_type;
        ScreenIndex addScreen(const Screen &entry_add);
        void clear(ScreenIndex entry_clear);

    private:
        vector<Screen> screens{Screen(24, 70, ' ')};
};

Window_Manager::ScreenIndex Window_Manager::addScreen(const Screen &entry_add) {
    screens.push_back(entry_add);
    return screens.size() - 1;
}

void Window_Manager::clear(ScreenIndex entry_clear) {
    Screen &screen_clear = screens[entry_clear];
    screen_clear.contents = string(screen_clear.height * screen_clear.width, ' ');
}

int main() {
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(cout);
    cout << "\n";
    myScreen.display(cout);
    cout << "\n";
}