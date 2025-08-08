#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Document
{
private:
  // list of elements for the document
  vector<string> elements;
  // rendered document
  string renderedDocument;

public:
  // add image functionality
  void addImg(string img)
  {
    elements.push_back(img);
  }
  // add text functionality
  void addText(string text)
  {
    elements.push_back(text);
  }
  // render document functionality
  string renderToFile()
  {
    if (renderedDocument.empty())
    {
      string result;
      for (string ele : elements)
      {
        // checking for image element
        if (ele.size() > 4 && ele.substr(ele.size() - 4) == ".jpg" || ele.substr(ele.size() - 4) == ".png")
        {
          result += "[Image: " + ele + "]\n";
        }
        else
        {
          result += ele + "\n";
        }
      }
      renderedDocument = result;
    }
    return renderedDocument;
  }

  // saving document functionality
  void saveToFile()
  {
    ofstream file("bad_document.txt");
    if (file.is_open())
    {
      file << renderedDocument;
      file.close();
    }
    else
    {
      cout << "Error: Failed to open the file\n";
    }
  }
};

int main()
{
  Document *editor = new Document();
  editor->addText("This is editor");
  editor->addImg("editor_image.jpg");
  cout << editor->renderToFile();
  editor->saveToFile();

  return 0;
}