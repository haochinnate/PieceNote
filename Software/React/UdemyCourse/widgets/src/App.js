import React, { useState } from 'react'
import Accordion from './components/Accordion'
import Search from './components/Search'
import Dropdown from './components/Dropdown'
import Translate from './components/Translate'
import Route from './components/Route'
import Header from './components/Header'

const items = [
  {
    "title": 'some title 1',
    "content": "content 1",
  },
  {
    "title": 'some title 2',
    "content": "content 2",
  },
  {
    "title": 'some title 3',
    "content": "content 3",
  }   
];

const options = [
  {
    "label": 'The color Red',
    "value": "red",
  },
  {
    "label": 'The color Green',
    "value": "green",
  },
  {
    "label": 'A Shade of Blue',
    "value": "blue",
  }   
];


// const showAccordion = () => {
//   if (window.location.pathname === '/') {
//     return <Accordion items={items}/>
//   }
// }

// const showList = () => {
//   if (window.location.pathname === '/list') {
//     return <Search />
//   }
// }

export default () => {
  const [selected, setSelected] = useState(options[0]);
  // const [showDropdown, setShowDropdown] = useState(true);

  return (
    <div>
      <Header />
      <Route path="/" >
        <Accordion items={items} />
      </Route>

      <Route path="/list" >
        <Search />
      </Route>

      <Route path="/dropdown" >
        <Dropdown 
          label="Select a color"
          options={options}
          selected={selected}
          onSelectedChange={setSelected}
        />
      </Route>

      <Route path="/translate" >
        <Translate/>
      </Route>
      {/* {showAccordion()}
      {showList()}
      {showDropdown()}
      {showTranslate()} */}
      {/* <br/> */}
      {/* <Accordion items={items}/> */}
      {/* <Search /> */}
      {/* <button onClick={() => setShowDropdown(!showDropdown)}>Toggle Dropdown</button>
      { showDropdown ?
        <Dropdown 
         options={options}
         selected={selected}
         onSelectedChange={setSelected}
       /> : null
      } */}
      {/* <Translate /> */}
    </div>
  );
};
