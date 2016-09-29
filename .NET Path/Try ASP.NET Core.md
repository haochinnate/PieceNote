(CodeSchool)

## 1-Model View Controller

### Introduction to MVC

1. User enters URL into browser. (Make a request)
2. Controller gets data from model based on the URL that was entered.     
   (Controller takes request to ask data in the model.)
3. Controller gives data to the view so it can display it in the browser.
   (Then Controller pass model data on to the view.)

#### Structure of an ASP.NET MVC Project

* Root (Folder matched the name of our project)
  * Models
    * Home.cs
  * Views
    * Home
      * Index.cshtml  
  * Controllers
    * HomeController.cs

#### cshtml

* cshtml is a template file that lets us use HTML- and C#-like code to generate our pages.
* To update the name dynamically, we need to: 
  * Update the view to accept data
  * Update the controller to send data
* When you're mixing HTML and C#, you're using a built-in engine called "Razor"

##### @model
* defines the type of data coming into the view
* tells our view what kind of data is coming in
* "@model string" <- Our view is expecting a single string of data.

##### @Model
* accessed the model data passed into the view
* gives us access to data passed into our view from a controller
* "@Model" <- Use the uppercase @Model to access whatever data gets passed into our view

#### HomeController.cs

* Methods that return IActionResult are called "action methods." Action methods provide responses usable by browsers.

### Basic Routes

<- start here next time

### Models

## 2-Getting User Input

### Application Need Input

## 3-Retaining Data

### Remembering Out Input