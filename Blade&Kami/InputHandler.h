#pragma once
#include <string>
#include <functional>

class InputHandler {
public:
    // �������� ����� ��� ��������� ��������� ����� �� ������������
    // ���������:
    // prompt - ��������� ��� ������������ (�������������)
    // clearInputBuffer - ����� �� ������� ����� ����� ����� �������� (�� ��������� true)
    static int getIntInput(std::function<void()> redrawCallback);
    static int NewInput();

private:
    // ��������������� ����� ��� ������� cin �� ������������� �����
    static void clearInputStream();

    // ��������, �������� �� ������ �������� ����� ������
    static bool isValidInteger(const std::string& str);
};