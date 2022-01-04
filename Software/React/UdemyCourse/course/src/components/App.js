import React from "react";
import Jsx from "./jsx/Jsx";
import Project2 from "./jsx/Project2";
import Header from "./widgets/Header";
import Route from './widgets/Route';
import Season from "./seasons/Season";


const App = () => {
  return (
    <div>
      <Header />

      <Route path="/jsx" >
        <Jsx />
      </Route>

      <Route path="/components" >
        <Project2 />
      </Route>

      <Route path="/seasons" >
        <Season />
      </Route>

    </div>
  );
}

export default App;
