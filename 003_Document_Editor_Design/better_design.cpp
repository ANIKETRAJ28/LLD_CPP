#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Abstract Element class to hold different types of elements
class Element
{
public:
  // virtual render function to render differnet types of elements
  virtual string render() = 0;
};

// Text class to hold Texts
class Text : public Element
{
private:
  string element;

public:
  Text(string text)
  {
    this->element = text;
  }
  string render() override
  {
    return element;
  }
};

// Image class to hold Images
class Image : public Element
{
private:
  string element;

public:
  Image(string img)
  {
    this->element = img;
  }
  string render() override
  {
    return "[Image: " + element + "]";
  }
};

// nextLine class to hold next line
class NextLine : public Element
{
private:
  string element = "\n";

public:
  string render() override
  {
    return element;
  }
};

class Persistance
{
public:
  virtual void save(string document) = 0;
};

class SaveToFile : public Persistance
{
public:
  void save(string document) override
  {
    ofstream file("better_design.txt");
    if (file.is_open())
    {
      file << document;
      file.close();
    }
    else
    {
      cout << "Error: Unable to open the file\n";
    }
  }
};

class SaveToDB : public Persistance
{
public:
  void save(string document) override
  {
    // save logic for db here...
  }
};

// Document class to hold elements and functionality related to elements
class Document
{
private:
  vector<Element *> elements;
  string renderedDocumnet;

public:
  // add elements to document function
  void addElement(Element *ele)
  {
    elements.push_back(ele);
  }

  // render document function
  void render()
  {
    if (!renderedDocumnet.empty())
      return;
    string result;
    for (Element *ele : elements)
    {
      result += ele->render();
    }
    renderedDocumnet = result;
  }

  void save(Persistance *persistance)
  {
    render();
    persistance->save(renderedDocumnet);
  }
};

class Editor
{
private:
  Document *document;
  Persistance *persistance;

public:
  Editor(Document *document, Persistance *persistance)
  {
    this->document = document;
    this->persistance = persistance;
  }
  void addText(string text)
  {
    document->addElement(new Text(text));
  }
  void addImage(string img)
  {
    document->addElement(new Image(img));
  }
  void addNextLine()
  {
    document->addElement(new NextLine());
  }
  void render()
  {
    document->render();
  }
  void save()
  {
    document->save(persistance);
  }
};

int main()
{
  Document *doc = new Document();
  Persistance *file = new SaveToFile();
  Editor *editor = new Editor(doc, file);
  editor->addImage("image.jpg");
  editor->addNextLine();
  editor->addText("new text");
  editor->save();

  return 0;
}