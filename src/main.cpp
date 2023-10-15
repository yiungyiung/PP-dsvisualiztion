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

// Base class for drawable objects
class Drawable
{
public:
    virtual void Draw() = 0; // Pure virtual function
    virtual ~Drawable() {}         // Virtual destructor
};

// Node class definition
class Node : public Drawable
{
public:
    Rectangle rect;
    string text;
    Node *next;
    bool canshow = false;
    // Constructor
    Node(Rectangle _rect, string _text, Node *_next = NULL) : rect(_rect), text(_text), next(_next) {}

    ~Node()
    {
        // Perform cleanup
        if (next != NULL)
        {
            delete next;
            next = NULL;
        }
    }
    // Method to draw the node
    void DrawNode () 
    {
        if (found && cansearch)
        {
            if (show == canshow)
            {
                DrawRectangleRec(Rectangle{rect.x - 2, rect.y - 2, rect.width + 4, rect.height + 4}, GREEN);
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
            DrawRectangleRec(Rectangle{rect.x - 2, rect.y - 2, rect.width + 4, rect.height + 4}, GREEN);
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
            DrawLineEx({rect.x + rect.width, rect.y + rect.height / 2}, {next->rect.x, next->rect.y + next->rect.height / 2}, 4, RED);
            DrawTriangle({next->rect.x, next->rect.y + next->rect.height / 2}, {next->rect.x - 10, next->rect.y + next->rect.height / 2 - 10}, {next->rect.x - 10, next->rect.y + next->rect.height / 2 + 10}, RED);
        }
    }

    void Draw()  override
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
            head = head->next;
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
            for (int i = 1; i < (pos - 1); i++)
            {
                current = current->next;
            }
            Node *nodeToRemove = current->next;
            current->next = nodeToRemove->next;
            delete nodeToRemove;
        }
        resetNodepos();
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

    // Initialization
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "DATA STRUCTURES VISUALIZATION");

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

        ClearBackground(DARKGRAY);
        // Draw the linked list using the LinkedList class
        if (GuiButton((Rectangle{1200, 520, 192, 72}), SEARCHText))
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
        DrawRectangleRec(Rectangle{312, 520, 152, 72}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{312, 696, 152, 72}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{312, 608, 152, 72}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{520, 696, 152, 72}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{1000, 696, 152, 72}, LIGHTGRAY);
        DrawRectangleRec(Rectangle{1400, 520, 152, 72}, LIGHTGRAY);
        if (GuiValueBox((Rectangle{1400, 520, 152, 72}), SearchText, &SearchITEMValue, 0, 100, SearchITEMEditMode))
        {
            SearchITEMEditMode = !SearchITEMEditMode;
        }
        if (GuiButton((Rectangle{96, 520, 192, 72}), Button000Text))
        {
            linkedList.AddNode(to_string(ValueBOx003Value));
            ValueBOx003Value = 0;
        }
        if (GuiValueBox((Rectangle{312, 520, 152, 72}), ValueBOx003Text, &ValueBOx003Value, 0, 100, ValueBOx003EditMode))
            ValueBOx003EditMode = !ValueBOx003EditMode;
        if (GuiButton((Rectangle{96, 608, 192, 72}), ADDBEGText))
        {
            linkedList.addBegin(to_string(ADDBEGVALValue));
            ADDBEGVALValue = 0;
        }
        if (GuiButton((Rectangle{96, 696, 192, 72}), ADDANYText))
        {
            linkedList.addAny(ADDANYPOSValue, to_string(ADDANYVALValue));
            ADDANYPOSValue = 0;
            ADDANYVALValue = 0;
        }
        if (GuiValueBox((Rectangle{312, 608, 152, 72}), ADDBEGVALText, &ADDBEGVALValue, 0, 100, ADDBEGVALEditMode))
            ADDBEGVALEditMode = !ADDBEGVALEditMode;
        if (GuiValueBox((Rectangle{312, 696, 152, 72}), ADDANYVALText, &ADDANYVALValue, 0, 100, ADDANYVALEditMode))
            ADDANYVALEditMode = !ADDANYVALEditMode;
        if (GuiValueBox((Rectangle{520, 696, 152, 72}), ADDANYPOSText, &ADDANYPOSValue, 0, 100, ADDANYPOSEditMode))
            ADDANYPOSEditMode = !ADDANYPOSEditMode;
        if (GuiButton((Rectangle{752, 616, 192, 72}), DELBEGText))
        {
            linkedList.removeNodeBegin();
        }
        if (GuiButton((Rectangle{752, 696, 192, 72}), DELANYText))
        {
            linkedList.removeAny(DELANYPOSValue);
        }
        if (GuiValueBox((Rectangle{1000, 696, 152, 72}), DELANYPOSText, &DELANYPOSValue, 0, 100, DELANYPOSEditMode))
            DELANYPOSEditMode = !DELANYPOSEditMode;
        if (GuiButton((Rectangle{752, 528, 192, 72}), DELENDText))
        {
            linkedList.removeNodeEnd();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
