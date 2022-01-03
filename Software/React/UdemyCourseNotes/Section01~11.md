
## Section 1

- components 負責兩件事情
  1. produces JSX
  2. handles user events

- JSX
  - set of instructions to tell React what content we want to show on the screen

- JSX elements, (Is this a DOM element?)
  - Tell React to create a normal HTML element
    - Yes, show the element on the screen
  - Or Tell React to show another component
    - No, call the component function and inspect all the JSX we get back

- bundle.js 會把所有需要的js 都回傳?

- index.js 內容
```js
// 1. 呼叫 App function(component), 取得JSX. 轉成HTML
// 2. 將這些HTML, 放在index.html DOM 中 id為"root" 的 element底下
ReactDOM.render(<App />, document.getElementById("root"));
```

- React vs. ReactDOM
  - React: 
    - Reconciler
    - Knows how to work with components
  - ReactDOM
    - Renderer
    - Knows how to take instructions on what we want to show and turn it into HTML 

- useState
  - Function for working with React 'state' system
  - State is used to keep track of data that changes over time
  - Used to make React update the HTML on the screen

- 檢查 node.js 安裝: node -v


- 安裝 create-react-app
  - > npm install -g create-react-app
  - -g: globally, can run it from the terminal
- 建立 React projects
  - > npx create-react-app jsx

- ES2015 幾乎都有支援, 2016以後 poor support, Bable 負責轉換到可以用的ES版本

- Project Directory
  - src: put all the source code we write
  - public: stores static files, like images
  - node_modules: contains all of our project dependencies
  - pakcage.json: records our project dependencies and configures our project
  - package-lock.json: records the exact version of pakcages that we install
  - README.md: instructions on how to use this project

- 啟動React app
  - > npm start
- 關閉React app
  - > Ctrl + C

- Javascript modules system
  - import React from 'react'
  - import 是 ES2015 statement, require 是 CommonJS statement
  - React: the variable we want to assign this import to
  - 'react': the name of the dependency or path to the file we are importing

```js
// Create a react component
const App = () => {
    return <div>Hi there!</div>;
}


// Take the react component and show it on the screen
ReactDOM.render(
    <App />,
    document.querySelector('#root')
);
```

## Section 2: Building Content with JSX

- babeljs.io 可以看到 JSX 如何轉成 javascript

- HTML to JSX, 如果直接把下面的 html 貼到 jsx 裡面會不認得

```html
<div>
  <label class="label" for="name" >Enter name:</label>
  <input id="name" />
  <button style="background-color: blue; color: white;">Submit</button>
</div>
```

- HTML vs. JSX
  - Adding custom styling to an element uses different syntax
    - style="background-color: red;"
    - style={{ backgroundColor: 'red' }}
    - 第一層{} 表示要用JSX的變數, 第二層{} 是一個 javascript object
  - Adding a class to an element uses  different syntax
    - class="label"
    - className="label", 為了避免跟 javascript 的 class 關鍵字衝突
  - JSX can reference JS variable
    - {buttonText}
    - {getButtonText()}, 呼叫 function
  - for -> htmlFor

- Values JSX can't show: javascript object {...}
```js
const buttonText = {text: 'click me'}; 

// 這個要用 {buttonText.text} 來顯示 
{buttonText.text}
```

## Section 3: Communicating with Props

- 內容在 \ReactPlayground\components 底下 

1. Component __Nesting__
2. Component __Reusability__
3. Component __Configuration__


- [Semantic UI](https://semantic-ui.com/)
- [Semantic UI CDN Link](https://cdnjs.com/libraries/semantic-ui)

- 放在 components\public\index.html 的 <head> 裡面
- 可以從 Inspect\Network\CSS 看到 semantic.min.css 有被載入
```html
<link
  rel="stylesheet"
  href="https://cdnjs.cloudflare.com/ajax/libs/semantic-ui/2.4.1/semantic.min.css"
/>
```

- 假資料來源[faker js](https://github.com/marak/Faker.js/)

```cmd
> npm install --save faker
// save 是指存在 local project
```

```js
import faker from 'faker'
<img alt="avatar" src={faker.image.avatar()}/>
```

- Create a Reusable Configurable Component
  - Identify the JSX that appears to be duplicated
  - What is the purpose of that block of JSX? Think of a descriptive name for what it does
  - Create a new file to house this new component - it should have the same name as the component
  - Create a new component in the new file, paste the JSX into it
  - Make the new component configurable by using React's 'props' system

- 要可以輸出 component 要加 "export default CommentDetail"
- import 是自動找 結尾是 .js的檔案

- Props
  - System for passing data from parent component to a child component
  - Goal is to customize or configure a child component

- Provide information: name of the prop->author, value of the prop->Sam

```js
<CommentDetail author="Sam"/>
<CommentDetail author="{author}"/>
```

- Consume information: (props), {props.author}

```js
const CommentDetail = (props) => {
    return (
        <a href="/" className="author">
            {props.author}
        </a>
    );
};
```

- props.children: 把 component 帶入到其他 component 中

```js
<ApprovalCard>
  <CommentDetail/>
</ApprovalCard>

const ApprovalCard = (props) => {
    console.log(props.children)
    <div className="content">{props.children}</div>
};
```

## Section 4: Structuring Apps with Class-Based Components

- 內容在 \ReactPlayground\seasons 底下 

- How React __Used to Be__
  - Functional Components
    - Can produce JSX to show content to the user
  - Class components
    - Can produce JSX to show content to the user
    - Can use the __lifecycle Method__ system to run code at specific points in time
    - Can use __'state'__ system to update content on the screen

- How React __Is Now__: Hooks System & Functional Components
  - Functional Components
    - Can use __Hooks__ to run code at specific points in time
    - Can use __Hooks__ to access state system and update content on screen


- Benefits of Class Components
  - Easier code organization
  - Easier to handle user input
  - Easier to do things when the app first starts


- [Geolocation API](developer.mozilla.org/en-US/docs/Web/API/Geolocation_API)

```js
window.navigator.geolocation.getCurrentPosition(
  // success callback
  (position) => console.log(position),
  // failure callback
  (err) => console.log(err)
);
```
- 差異:
  - GeolocationPositionError vs. PositionError
  - GeolocationPosition vs. Position

- 在 browser 中 開啟 app 的 timeline
  - JS file loaded by browser
  - App component gets created
  - Call Geolocation service
  - App returns JSX, gets rendered to page as HTML
  - ...
  - We get result of geolocation
  - __Tell the component to rerender with new information__

- 為了解決這個問題: 用 class component + react state

- Rules of Class components:
  - Must be a Javascript Class
  - Must extend React.Component
  - Must define a 'render' method that return some JSX


```js
class App extends React.Component {
    // React says we have to define render()!!!
    render() {
        return (
            <div>Hi there!</div>
        );
    }
}
```

## Section 5: State in React Components

- 內容在 \ReactPlayground\seasons 底下 

- Rules of State
  - Only usable with class components
  - You will confuse props with state
  - 'State' is a JS object that contains data relevant to a component
  - Updating 'state' on a component causes the component to (almost) instantly rerender
  - __State must be initialized when a component is created__
  - __State can only be updated using the function 'setState'__


```js
// 初始化
constructor(props) {
    super(props);

    this.state = {latitude: null};
}

// 使用
<div>Latitude: {this.state.latitude}</div>

// 設定, call setState
this.setState({latitude: position.coords.latitude});

// 除了 初始化以外 不會用下面這樣來update, 都用 setState
this.state.latitude = position.coords.latitude
```

- render() 會被呼叫很多次, 所以不要在這邊放 初始化或很花時間的東西

- Handling error, 增加一個 state: errorMessage

```js
this.state = {latitude: null, errorMessage: ''};

this.setState({ errorMessage: err.message })
```

- Conditionally Rendering Content

```js
render() {
  if (this.state.errorMessage && !this.state.latitude) {
    return <div>Error: {this.state.errorMessage}</div>
  }
  if (!this.state.errorMessage && this.state.latitude) {
    return <div>Latitude: {this.state.latitude}</div>
  }
        
  return <div>Loading</div>
}
```

## Section 6: Understanding Lifecycle Methods

- 內容在 \ReactPlayground\seasons 底下 

- Component Lifecycle
  - constructor
    - Good place to do one-time setup
  - render
    - Avoid doing anything besides returning JSX
  - (content visible on screen)
  - componentDidMount
    - Good place to do data-loading
  - (sit and wait for updates)
  - componentDidUpdate
    - Good place to do more data-loading when state/props change
  - (sit and wait until this component is no longer shown)
  - componentWillUnmount
    - Good place to cleanup(especially for non-React stuff)

- 另外還有不常用的
  - shouldComponentUpdate
  - getDerivedStateFromProps
  - getSnapshotBeforeUpdate

- 把讀取位置的function 移到 componentDidMount中
- 把初始化 state 移出 constructor

```js
state = { latitude: null, errorMessage: '' };
// 跟在 constructor 中做是一樣的, Babel 會幫忙處理
```

- 把 state 傳入 child 當作 props

```js
<SeasonDisplay lat={this.state.latitude}/>
const SeasonDisplay = (props) => {
    return (<div>SeasonDisplay {props.lat}</div>)
}
```

- 取得月份
```js
new Date().getMonth()
```

- ICONS-[SemanticUI](https://semantic-ui.com/elements/icon.html#/definition)

```js
<i class="disabled users icon"></i>
<i className={`${icon} icon`}></i>

const {text, iconName} = seansonConfig[season] // this is object: {text, iconName}
<i className={`massive ${iconName} icon`}></i> // 利用 class 決定 icon 大小
```

- 建立 .css 檔案 放 styling, 使用的地方要 import
```js
import './SeasonDisplay.css';
.className {

}

// class 是 season-display + summer 底下的 <i> 要套用此設定
.season-display.summer i {
    color: red;
}
```

- default props
```js
Spinner.defaultProps = {
    message: 'Loading...'
};
```

- Helper function, 在render()裡面盡量不要有判斷式, 改放在另一個 function(renderContent)裡面
```js
render() {
  return (
    <div className="border red">
      {this.renderContent()}
    </div>
  );
};
```

## Section 7: Handling User Input with Forms and Events

- 內容在 \ReactPlayground\pics 底下 

- 處理 user 的 input
```js
onInputChange(event) {
  console.log(event.target.value);
}

<input type="text" onChange={this.onInputChange} />
```

- 通常的命名規則: on/handle-ElementName-EventName

- some event
  - onClick: user clicks on something
  - onChange: user changes text in an input
  - onSubmit: user submits a form

- 另一種方式, arrow function
```js
<input type="text" onChange={(e) => {
  console.log(e.target.value);
}} />
```

- Uncontrolled vs. Controlled Elements
  - 把值存在 React component(state中), 而非 html DOM 中
```js
state = { term: '' };

<input type="text"
  value={this.state.term} 
  onChange={(e) => this.setState({ term: e.target.value.toUpperCase() })}
/>              
```

- 預設按下enter後, form會整個重新整理, 自己處理 form 的 onSubmit
```js
onFormSubmit(event) {
  event.preventDefault();
}
<form className="ui form" onSubmit={this.onFormSubmit}>

</form>
```

- Javascript 裡面的 this
  - Error message: "Cannot read property 'state' of undefined"
  - javascript 覺得 form 裡面的 __this__ 不是 component, 而是 undefined
  - this, 不是看 method 本身, 而是 __在哪邊__ call 這個 method
  - 
```js
onFormSubmit(event) {
  event.preventDefault();
  console.log(this.state.term); // this will has undefined error
}

// Example ---------------
// 正常情況
const car = new Car();
car.drive();
// 在 drive() 裡面, this 就是 car
// 看 function "." 的左邊是什麼 

// 另一種情況 
const truck = {
  sound: 'putputput',
  driveMyTruck: car.drive
}

truck.driveMyTruck(); // 這個會 output 'putputput' 

// 另一種情況 
const drive = car.drive;
drive() // 這個就會有 undefined error
```

- 解決方式
  1. 建立 constructor, bind function, 然後 override 原本的function
  2. 呼叫的 function 用 arrow function 宣告, 用幫忙 bind
  3. 在 JSX 裡面就用 arrow function 呼叫 宣告的 onFormSubmit

```js
// 1
this.drive = this.drive.bind(this)

// 2. 
onFormSubmit = (event) => {
  console.log(this); // original will be undefined
};

// 3. 
onSubmit = {(event) => this.onFormSubmit(event)}
```

- communicating child to parent
  - 把 App 重構成 class component
  - 宣告 method 當作 props 丟給 child
  - 有更改時, child 利用 method 把資料回給 parent

```js
// in App.js
onSearchSubmit(term) {
  console.log(term);
}
<SearchBar onSubmit={this.onSearchSubmit}/>


// in SearchBar.js
onFormSubmit = (event) => {
  event.preventDefault();

  this.props.onSubmit(this.state.term);
};
// 在 class component 裡面 props 要用 this
```

## Section 8: Making API Requests with React

- 內容在 \ReactPlayground\pics 底下 

- [Unsplash API](https://unsplash.com/developers), 註冊並建立 application
  - [Search photo](https://unsplash.com/documentation#search-photos) 
  - [Schema-Location](https://unsplash.com/documentation#location)
  - 使用 axios 的URL: https://api.unsplash.com/
  - [Authorization](https://unsplash.com/documentation#public-authentication) 
    - in header Authorization: Client-ID YOUR_ACCESS_KEY 
    - query parameter: ?client_id=YOUR_ACCESS_KEY

- AJAX Client <-> Unsplash API, 安裝 axios
  - axios: 3rd party package, 處理 html request
  - fetch: function built into modern browsers

```cmd
npm install --save axios
```

```js
import axios from 'axios'

// GET /search/photos
onSearchSubmit(term) {
  axios.get('https://api.unsplash.com/search/photos', {
    params: { query: term },
    headers: {
      Authorization: 'Client-ID YOUR_ACCESS_KEY',
    }
  });
};

// 從 Network 頁面點選request, 然後在Preview中可以看到結果
// 目標在: results[idx].urls.regular 
```

- Handling request with Async Await
```js

// 方法1: axios.get 會回傳一個 Promise 的物件, 再呼叫 then() 表示完成 request 之後要做的事情
axios.get('https://api.unsplash.com/search/photos', {
  // params, headers, etc...            
}).then((response) => {
  // request.data.results[idx].urls.regular 
  console.log(response.data.results);
});

// 方法2: 在 function 前面 + async, axios 前面 + await
async onSearchSubmit(term) {
  const response = await axios.get('https://api.unsplash.com/search/photos', {
    // params, headers, etc...            
  });

  console.log(response.data.results)
}
```

- 將取得的存到 state 中
```js
state = { images: [] };
        
this.setState({ images: response.data.results })

// async function 改為 arrow function
onSearchSubmit = async (term) => {
  const response = await axios.get();
}
```

- 建立新資料夾 \src\api, 將 axios 一些放在這邊
```js
export default axios.create({
    baseURL: 'https://api.unsplash.com',
    headers: {
        Authorization: 'Client-ID rv6PCRLx9oyFlKFWixJAke__uvkqjB0ItWWXiCz5Sik',
    }
});

// 使用變成
import unsplash from '../api/unsplash'
const response = await unsplash.get('/search/photos', {
  params: { query: term }
});
```

## Section 9: Building Lists of Records

- 內容在 \ReactPlayground\pics 底下 

- map statement in javascript
```js
const numbers = [ 0, 1, 2, 3, 4];
let newNumbers = [];

for (let i = 0; i < numbers.length; i++) {
  newNumbers.push(numbers[i] * 10);
}

// 等同於
newNumbers = numbers.map((num) => {
  return num * 10;
});

numbers.map((num) => num * 10);
```

```js
// 在 return 的 root element 加上 key 就好了
const images = props.images.map((image) => {
  return <img key={image.id} src={image.urls.regular}></img>
});
```

## Section 10: Using Ref's for DOM Access

- 內容在 \ReactPlayground\pics 底下 

- 建立 ImageList.css, 在裡面加 style
```js
<div style="display: grid">
</div>
```

- destructure 
```js
const { description, urls } = this.props.images; 
```

- Accessing the DOM with Refs
  - Give access to a single DOM element
  - create __Refs__ in constructor, assign them to instance variable, then pass to particular JSX elements as props
  - 動態決定高度

```js
constructor(props) {
  super(props);

  this.imageRef = React.createRef();
}

<img ref={this.imageRef}/>
        
this.imageRef.current.addEventListener('load', this.setSpans);

setSpans = () =>  {
  const height = this.imageRef.current.clientHeight;
  const spans = Math.ceil(height / 150);

  this.setState({ spans: spans });
}

this.state = { spans: 0 };
<div style={{ gridRowEnd: `span ${this.state.spans}`}}>
</div>
```

## Section 11: Let's Test Your React Mastery!

- 原本另外建立一個 projects: videos, 改一樣放在 pics底下

- YouTube API
  - 先到 console.developers.google.com 建立專案
  - YouTube Data API v3, 選 Enable
  - Create credentials
  - 取得 API key, 增加存取限制
  - 建立新的 \src\api\youtube.js
  
- youtube.js
```js
// GET https://www.googleapis.com/youtube/v3/search
export default axios.create({
    baseURL: 'https://www.googleapis.com/youtube/v3',
    params: {
        part: 'snippet',
        type: 'video',
        maxResults: 5,
        key: KEY
    }
});
```

- 呼叫 API, 得到 response
```js
// 參考文件: https://developers.google.com/youtube/v3/docs/search/list
onSearchVideoSubmit = async (term) => {
  console.log(term)
  const response = await youtube.get('/search', {
    params: { q: term }
  });
  console.log(response)
}
```

- 解析 response
```js
this.setState({ videos: response.data.items });
```

- Communicating from child(VideoItem) to parent(App.js)
```js
// in App.js

<VideoList onVideoSelect={this.onVideoSelect} />
onVideoSelect = (video) => {
  // callback function
  console.log('From the App!', video);
}

// in VideoList.js, pass callback function to VideoItem
return (<VideoItem video={video} onVideoSelect={props.onVideoSelect} />);


// in VideoItem.js
const VideoItem = ( {video, onVideoSelect} ) => {
  <div className="video-item item" onClick={() => onVideoSelect(video)}>
    ...
  </div>
}

// whick click, will call the callback function
```

- string interpolation
```js
const videoSrc = `https://www.youtube.com/embed/${video.id.videoId}`;

```

- [semantic-ui 的 grid](https://semantic-ui.com/collections/grid.html)
