# Hooks System

- Learn Class components -> Learn Hooks -> Learn Redux

- useState: Function that lets you use __state__ in a functional component
- useEffect: Function that lets you something like __lifecycle methods__ in a functional component
- useRef: Function that lets you create a __ref__ in a functional component

- Primitive Hooks, 可以用這些, 自己建立 Custom Hook
  - useState
  - useEffect
  - useContext
  - useReducer
  - useCallback
  - useMemo
  - useRef
  - useImperativeHandle
  - useLayoutEffect
  - useDebugValue

- 專案內容在 \reactplayground\widgets

#### Helper function in function component

```js
const renderItems = items.map((item, index) => {
    // ...
    onClick={() => console.log('Title clicked', index)}>
    // ...
}
```

- 另外宣告 helper function
```js
const onTitleClick = (index) => {
    console.log('Title clicked', index)
};

onClick={() => onTitleClick(index)}>

// 如果是下面這樣, 會在 render 的時候就呼叫了 
onClick={onTitleClick(index)}>
```

#### useState

##### state in class component

```js
// Initialize value of state
state = { activeIndex: 0 };

// Value only changed through 'setState' function
this.setState({
  activeIndex: index
});

// Reference value through 'this.state'
{this.state.activeIndex}
```

##### In hook system (Accordion.js)

```js
import React, { useState } from 'react'

// activeIndex is the state you want to track of
// setActiveIndex is the function to update value of state
// null 是 預設值
const [activeIndex, setActiveIndex] = useState(null);

setActiveIndex(index);

<h1>{activeIndex}</h1>
```

```js
const [firstElement, secondElement] = colors;
// 意思是 把 colors[0] 放到 firstElement, 而 colors[1] 放到 secondElement

const [counter, setCounter] = useState(0)
const [color, setColor] = useState("green")

// 多個 state 的情況, hooks with function components 需要下多行
```

```js
// 判斷值, 得到 class 的 string
const active = index === activeIndex ? 'active' : 'string';

// 然後 interpolation 設定到 className
className={`content ${active}`}
```

#### useEffect

##### 簡介

- Allows function components to use something like lifecycle methods
- We configure the hook to run some code automatically in one of three scenarios
  1. When the component is rendered for the first time only
    - []
  2. When the component is rendered __for the first time and whenever it rerenders__
    - 沒參數
  3. When the component is rendered __for the first time and (whenever it rerenders and some piece of data has changed)__
    - [data]


##### 實例 in course(Search.js)

- 用到 wikipedia API
  - https://en.wikipedia.org/w/api.php?action=query&list=search&origin=*&format=json&srsearch=$TERM$

```js
import React, { useState, useEffect } from 'react'

useEffect(() =>{
    console.log('some call useEffect!!')
}, [term]);
// 第二個參數可能是 
// 1. 沒參數不設定 => Run at initial render, run after every rerender
// 2. 空陣列[] => Run at initial render 
// 3. 或是陣列有值 [term, ajeiwjei, ...] => Run at initial render, Run after every rerender if data has changed since last render 
```

- 在 useEffect 裡的 arrow function, 沒辦法直接用 async, await
```js
// 改成在裡面再宣告一個 async function, 再呼叫他
useEffect(() =>{
    const searchWiki = async () => {
        await axios.get('...');
    };
  
    searchWiki();

    // 或是 define後, 馬上呼叫
    (async () => {
        await axios.get('...');
    })();

    // 或是用 then function 回傳的 promise 物件
    axios.get('...').then((response) => {});
}, [term]);
```

#### XSS Attacks in React

- wikipedia API 回傳的結果已經是 html 了

```js
<span dangerouslySetInnerHTML={{ __html: result.snippet }}></span>
```

#### 計時 timeout, clean up in useEffect

- useEffect 裡面的第一個參數 arrow function 裡面, 唯一能回傳的東西是 一個 arrow function, 會做 clean up

```js
useEffect(() => {
  console.log('Initial render or term was changed');

  const timeoutId = setTimeout(() => {
    if (term) {
      searchWiki();            
    }    
  }, 500);

  // changed 的時候, 會先執行 return function (呼叫 clean up), 再印出 上面那行 
  // 下一個 useEffect 要呼叫的時候, 會執行這個 return function
  return () => {
    console.log('Cleanup');
    clearTimeout(timeoutId);
  };
}, [term]);
```

#### useEffect advanced topics: debounced

- 參考 Search.js

- warning: React Hook useEffect has a missing dependency: 'results.length'. Either include it or remove the dependency array  react-hooks/exhaustive-deps
  - useEffect 有用到 useState: results(results.length), 但是 dependency array([term]) 裡面 沒有 results
  - 如果直接加入 dependency array, 變成 [term, reuslts.length] 的話, 剛開app 會變成 兩次 API request
  - 解決方式: 引入第二個 state: debouncedTerm
    1. Initial component render: term==='programming', debouncedTerm ==='programming'
    2. 用兩個 useEffect function 來去 watch 這兩個 state 
    3. 使用者輸入東西的時候 (馬上更新 update 'term'), 設定一個 timer 來 update 'debouncedTerm'
    4. 等到 timer 時間到後, update 'debouncedTerm' 的值, 再來用 debouncedTerm 值 call API 得到 data


#### useRef

##### 前情提要

- Event Bubbling
  - 在 DOM 裡面 child components 的 event 發生後, 會一路往上冒泡到所有 parent components, 如果也指定相同的 event handler, 就也會執行

- Dropdown 在 body element 設定一個 manual event listener. A click on any element will bubble up to the body!
  - manual 的 event listener會先執行, 才執行 react 的 event handler

```js
document.body.addEventListener('click', () => {
  console.log('CLICK!!')
})

// 在 component 裡面, 用 useEffect, 來設定上述的 click event, 只做一次所以用 []
useEffect(() => {
    document.body.addEventListener('click', () => {
        setOpen(false);
    }, { capture: true});
}, []);

// 加了這個 event listener後, 會影響原本的功能, 所以希望區分為兩個情況: 
// 到底是component 內部或外部的 click -> 利用 event.target 來判斷
if(ref.current.contains(event.target)) {
  return;
}
```

##### 簡介

- useRef: ref, Direct reference to a DOM element

##### 實例 in course(Dropdown.js)

- useState
```js
// Dropdown, 控制 "visible active" 和 "visible transition" 決定要不要顯示選項
className={`ui selection dropdown ${open ? 'visible active' : ''}`}>
className={`menu ${open ? 'visible transition' : ''}`}>
```

```js
import React, { useState, useEffect, useRef } from 'react';

// 宣告
const ref = useRef();

// 綁某個 element
<div ref={ref} className="ui form">

</div>


// 得到目前的 element
console.log(ref.current);
// 判斷 event 發生的目標是不是有包含在我們在意的 ref element 裡面
if(ref.current.contains(event.target)) {
  return;
}
```

##### null 的情況, 需要 removeEventListener

```js
// 如果 Dropdown component 不存在(hidden), 但是又 click 在body的位置,  addEventListener 還有的話, 還會觸發的話 
// 會造成 ref.current 是 null
// 所以需要在 useEffect 做 cleanup

return () => {
    document.body.removeEventListener('click', onBodyClick, { capture: true });
};

```

#### Translate Widget

- [Google Translate API Docs](cloud.google.com/translate/docs)
  - this is paid API
- POST https://translation.googleapis.com/language/translate/v2
  - query parameter
    - q: term
    - target: language code
    - key: API key

- response
  - data.translation[0].translatedText
  
```js
useEffect(() => {
    const doTranslation = async () => {
        // post 的回傳 直接用 { data } 將 response 中的資料取出
        // data.translation[0].translatedText
        const { data } = await axios.post(...);
    };
}, [language, text])
```

- 這邊一樣會送兩次 request, 可以參考 Search.js 做 debounced

#### Custom Hooks

##### Intro

- Best way to create reusable code in a React project(besides components)
- Created by extracting hook-related code out of a function component
  - not JSX
- Always make use of at least one primitive hook internally
- Each custom hook should have one purpose
- Kind of an art form!
- Data-fetching is a great thing to try to make reusable

##### Process For Creating Reusable Hooks

1. Identify each line of code related to some single purpose
2. Identify the __Inputs__ to that code
3. Identify the __Outputs__ to that code
4. Extract all of the code into separate function, receving the inputs as arguments, and returning the ouputs

- 測試 Inputs & Outputs 語句
  - If you give me a ???
  - I will give you ???

##### Example

- for "video fetching logic", reusable in different component
- 建立一個新資料夾 \src\hooks
- 在裡面建立新檔案for Custom hook: useVides.js

```js

// input: default search term
// output: videos, onTermSubmit(search)

const useVideo = (defaultSearchTerm) => {
  
  // some code...
  // 用 [] {} 都可以, 看習慣
  return [videos, search];
  // return { videos, search };
}

```

- 使用 Custom Hooks


```js
import useVideos from '../hooks/useVideos';

const [videos, search] = useVideos('peugeot 3008');
        
useEffect(() => {
  setSelectedVideo(vidoes[0]);
}, [videos]);

<SearchBarHooks onSubmit={search}/>

```

##### Warning

- React Hook useEffect has a missing dependency: 'defaultSearchTerm'. Either include it or remove the dependency array  react-hooks/exhaustive-deps
- React 會希望 useEffect 裡面有用到的 property, 要加入 dependency

```js
// 解決方式: 加入 [defaultSearchTerm]
useEffect(() => {
    // set some default searching
    search(defaultSearchTerm);
}, [defaultSearchTerm]);
```