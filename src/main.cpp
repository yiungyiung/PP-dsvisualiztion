#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <string>
#include <iostream>
using namespace std;

class Node;

int dist = 75;
int countdist = 1;
Node *head = NULL;
bool cansearch = false;
int item;
bool show = false;
bool found = false;

const float BASE_WIDTH = 1600.0f;
const float BASE_HEIGHT = 900.0f;

float scaleX, scaleY;

class Drawable
{
public:
    virtual void Draw() = 0;
    virtual ~Drawable() {}
};

class Node : public Drawable
{
public:
    Rectangle rect;
    string text;
    Node *next;
    bool canshow = false;

    Node(Rectangle _rect, string _text, Node *_next = NULL) : rect(_rect), text(_text), next(_next) {}

    ~Node()
    {
        if (next != NULL)
        {
            delete next;
            next = NULL;
        }
    }

    void DrawNode()
    {
        if (found && cansearch)
        {
            if (show == canshow)
            {
                DrawRectangleRec(Rectangle{rect.x - 2 * scaleX, rect.y - 2 * scaleY, rect.width + 4 * scaleX, rect.height + 4 * scaleY}, GREEN);
                if (text == to_string(item))
                {
                    DrawRectangleRec(rect, DARKGREEN);
                    found = true;
                }
                else
                {
                    DrawRectangleRec(rect, BLUE);
                }
            }
            else
            {
                DrawRectangleRec(rect, BLUE);
            }
        }

        else if (cansearch)
        {
            canshow = true;
            DrawRectangleRec(Rectangle{rect.x - 2 * scaleX, rect.y - 2 * scaleY, rect.width + 4 * scaleX, rect.height + 4 * scaleY}, GREEN);
            if (text == to_string(item))
            {
                DrawRectangleRec(rect, DARKGREEN);
                found = true;
            }
            else
            {
                DrawRectangleRec(rect, BLUE);
            }
        }
        else
        {
            canshow = false;
            DrawRectangleRec(rect, BLUE);
        }

        int textWidth = MeasureText(text.c_str(), 20);
        int textX = rect.x + (rect.width - textWidth) / 2;
        int textY = rect.y + (rect.height - 20) / 2;

        DrawText(text.c_str(), textX, textY, 20, WHITE);

        if (next != NULL)
        {
            DrawLineEx({rect.x + rect.width, rect.y + rect.height / 2}, {next->rect.x, next->rect.y + next->rect.height / 2}, 4 * scaleX, RED);
            DrawTriangle({next->rect.x, next->rect.y + next->rect.height / 2}, {next->rect.x - 10 * scaleX, next->rect.y + next->rect.height / 2 - 10 * scaleY}, {next->rect.x - 10 * scaleX, next->rect.y + next->rect.height / 2 + 10 * scaleY}, RED);
        }
    }

    void Draw() override
    {
        DrawNode();
    }

    void UpdatePos(Rectangle _rect)
    {
        rect = _rect;
    }

    friend class LinkedList;
};

// LinkedList class definition
class LinkedList
{
public:
    // Method to draw the linked list
    void DrawLinkedList()
    {
        Node *current = head;
        while (current != NULL)
        {
            current->DrawNode();
            current = current->next;
        }
    }
    void AddNode(string text)
    {

        if (head == NULL)
        {
            // If the list is empty, the new node becomes the head
            Node *newNode = new Node(Rectangle{(float)(countdist * dist), 100, 50, 50}, text);
            head = newNode;
            cout << countdist * dist << endl;
            countdist = 1;
        }
        else
        {
            // Otherwise, traverse the list to the end and add the new node
            Node *current = head;
            countdist++;
            while (current->next != NULL)
            {
                current = current->next;
                countdist++;
            }
            cout << countdist << endl;
            Node *newNode = new Node(Rectangle{(float)(countdist * dist), 100, 50, 50}, text);
            current->next = newNode;
            countdist = 1;
        }
    }
    void addBegin(string text)
    {
        if (head == NULL)
        {
            Node *newNode = new Node(Rectangle{(float)(countdist * dist), 100, 50, 50}, text);
            head = newNode;
            cout << countdist * dist << endl;
            countdist = 1;
        }
        else
        {
            Node *newNode = new Node(Rectangle{(float)(countdist * 1), 100, 50, 50}, text);
            newNode->next = head;
            head = newNode;
            resetNodepos();
        }
    }
    void addAny(int pos, string text)
    {
        if (pos < 0)
        {
            return;
        }
        else if (pos == 1)
        {
            addBegin(text);
        }
        else
        {
            Node *current = head;
            for (int i = 1; i < (pos - 1); i++)
            {
                current = current->next;
            }
            if (current != NULL)
            {
                if (current->next != NULL)
                {
                    Node *nodeToRemove = current->next;
                    Node *newNode = new Node(Rectangle{(float)(countdist * 1), 100, 50, 50}, text);
                    current->next = newNode;
                    newNode->next = nodeToRemove;
                }
                else
                {
                    AddNode(text);
                }
                resetNodepos();
            }
        }
    }
    void removeNodeBegin()
    {
        if (head != NULL)
        {
            Node *nodeToRemove = head;
            head = nodeToRemove->next;
            nodeToRemove->next = NULL;
            delete nodeToRemove;
        }
        resetNodepos();
    }

    void removeNodeEnd()
    {
        if (head != NULL)
        {
            Node *current = head;
            while (current->next->next != NULL)
            {
                current = current->next;
            }
            delete current->next;
            current->next = NULL;
        }
    }

    void removeAny(int pos)
    {
        if (pos < 0 || head == NULL)
        {
            return;
        }
        else if (pos == 1)
        {
            removeNodeBegin();
        }
        else
        {
            Node *current = head;
            for (int i = 1; i < (pos - 1) && current != NULL; i++)
            {
                current = current->next;
            }
            if (current != NULL && current->next != NULL)
            {
                Node *nodeToRemove = current->next;
                current->next = nodeToRemove->next;
                nodeToRemove->next = NULL;
                delete nodeToRemove;
                resetNodepos();
            }
        }
    }
    void resetNodepos()
    {
        countdist = 1;
        Node *current = head;
        while (current != NULL)
        {
            current->UpdatePos(Rectangle{(float)(countdist * dist), 100, 50, 50});
            current = current->next;
            countdist++;
        }
        countdist = 1;
    }
};

int main(void)
{

    const int baseScreenWidth = 1600;
    const int baseScreenHeight = 900;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(baseScreenWidth, baseScreenHeight, "LINKED LIST VISUALIZATION");

    scaleX = GetScreenWidth() / BASE_WIDTH;
    scaleY = GetScreenHeight() / BASE_HEIGHT;

    SetTargetFPS(25);

    // Create nodes for the linked list

    // Connect nodes to form a linked list
    // Create a LinkedList object and set the head
    LinkedList linkedList;

    // Const text
    const char *Button000Text = "ADD NODE END";          // BUTTON: Button000
    const char *ADDBEGText = "ADD NODE BEGINNING";       // BUTTON: ADDBEG
    const char *ADDANYText = "ADD NODE ANY POSITION";    // BUTTON: ADDANY
    const char *DELBEGText = "DELETE NODE BEGINNING";    // BUTTON: DELBEG
    const char *DELANYText = "DELETE NODE ANY POSITION"; // BUTTON: DELANY
    const char *DELENDText = "DELETE NODE END";          // BUTTON: DELEND
    const char *SEARCHText = "Search Item";

    // buttons and valuebox
    bool ValueBOx003EditMode = false;
    int ValueBOx003Value = 0;
    bool ADDBEGVALEditMode = false;
    int ADDBEGVALValue = 0; // ValueBOx: ADDBEGVAL
    bool ADDANYVALEditMode = false;
    int ADDANYVALValue = 0; // ValueBOx: ADDANYVAL
    bool ADDANYPOSEditMode = false;
    int ADDANYPOSValue = 0; // ValueBOx: ADDANYPOS
    bool DELANYPOSEditMode = false;
    int DELANYPOSValue = 0;
    bool SearchITEMEditMode = false;
    int SearchITEMValue = 0;

    // char *values
    char *ValueBOx003Text;
    char *ADDBEGVALText;
    char *ADDANYVALText;
    char *ADDANYPOSText;
    char *DELANYPOSText;
    char *SearchText;
    GuiSetStyle(DEFAULT, TEXT_SIZE, 12);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0xC0C0C0FF);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0x010101FF);
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x010101FF);
    GuiSetStyle(VALUEBOX, BASE_COLOR_NORMAL, 0x010101FF);
    GuiSetStyle(VALUEBOX, TEXT_COLOR_NORMAL, 0x010101FF);
    GuiSetStyle(VALUEBOX, BORDER_COLOR_NORMAL, 0x010101FF);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (IsWindowResized())
        {
            scaleX = GetScreenWidth() / BASE_WIDTH;
            scaleY = GetScreenHeight() / BASE_HEIGHT;
        }
        ClearBackground(DARKGRAY);
        // Draw the linked list using the LinkedList class
        if (GuiButton((Rectangle{1200 * scaleX, 520 * scaleY, 192 * scaleX, 72 * scaleY}), SEARCHText))
        {
            cansearch = !cansearch;
            item = SearchITEMValue;
            show = !show;
            if (found)
            {
                found = false;
            }
        }
        linkedList.DrawLinkedList();
        DrawRectangleRec(Rectangle{312 * scaleX, 520 * scaleY, 152*scaleX, 72 * scaleY}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{312 * scaleX, 696 * scaleY, 152 * scaleX, 72 * scaleY}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{312 * scaleX, 608 * scaleY, 152 * scaleX, 72 * scaleY}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{520 * scaleX, 696 * scaleY, 152 * scaleX, 72 * scaleY}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{1000 * scaleX, 696 * scaleY, 152 * scaleX, 72 * scaleY}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{1400 * scaleX, 520 * scaleY, 152 * scaleX, 72 * scaleY}, LIGHTGRAY);
        if (GuiValueBox((Rectangle{1400 * scaleX, 520 * scaleY, 152 * scaleX, 72 * scaleY}), SearchText, &SearchITEMValue, 0, 100, SearchITEMEditMode))
        {
            SearchITEMEditMode = !SearchITEMEditMode;
        }
        if (GuiButton((Rectangle{96 * scaleX, 520 * scaleY, 192 * scaleX, 72 * scaleY}), Button000Text))
        {
            linkedList.AddNode(to_string(ValueBOx003Value));
            ValueBOx003Value = 0;
        }
        if (GuiValueBox((Rectangle{312 * scaleX, 520 * scaleY, 152 * scaleX, 72 * scaleY}), ValueBOx003Text, &ValueBOx003Value, 0, 100, ValueBOx003EditMode))
            ValueBOx003EditMode = !ValueBOx003EditMode;
        if (GuiButton((Rectangle{96 * scaleX, 608 * scaleY, 192 * scaleX, 72 * scaleY}), ADDBEGText))
        {
            linkedList.addBegin(to_string(ADDBEGVALValue));
            ADDBEGVALValue = 0;
        }
        if (GuiButton((Rectangle{96 * scaleX, 696 * scaleY, 192 * scaleX, 72 * scaleY}), ADDANYText))
        {
            linkedList.addAny(ADDANYPOSValue, to_string(ADDANYVALValue));
            ADDANYPOSValue = 0;
            ADDANYVALValue = 0;
        }
        if (GuiValueBox((Rectangle{312 * scaleX, 608 * scaleY, 152 * scaleX, 72 * scaleY}), ADDBEGVALText, &ADDBEGVALValue, 0, 100, ADDBEGVALEditMode))
            ADDBEGVALEditMode = !ADDBEGVALEditMode;
        if (GuiValueBox((Rectangle{312 * scaleX, 696 * scaleY, 152 * scaleX, 72 * scaleY}), ADDANYVALText, &ADDANYVALValue, 0, 100, ADDANYVALEditMode))
            ADDANYVALEditMode = !ADDANYVALEditMode;
        if (GuiValueBox((Rectangle{520 * scaleX, 696 * scaleY, 152 * scaleX, 72 * scaleY}), ADDANYPOSText, &ADDANYPOSValue, 0, 100, ADDANYPOSEditMode))
            ADDANYPOSEditMode = !ADDANYPOSEditMode;
        if (GuiButton((Rectangle{752 * scaleX, 616 * scaleY, 192 * scaleX, 72 * scaleY}), DELBEGText))
        {
            linkedList.removeNodeBegin();
        }
        if (GuiButton((Rectangle{752 * scaleX, 696 * scaleY, 192 * scaleX, 72 * scaleY}), DELANYText))
        {
            linkedList.removeAny(DELANYPOSValue);
        }
        if (GuiValueBox((Rectangle{1000 * scaleX, 696 * scaleY, 152 * scaleX, 72 * scaleY}), DELANYPOSText, &DELANYPOSValue, 0, 100, DELANYPOSEditMode))
            DELANYPOSEditMode = !DELANYPOSEditMode;
        if (GuiButton((Rectangle{752 * scaleX, 528 * scaleY, 192 * scaleX, 72 * scaleY}), DELENDText))
        {
            linkedList.removeNodeEnd();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
