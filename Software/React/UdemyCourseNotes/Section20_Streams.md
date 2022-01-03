# Streams

- 內容在 \streams 中
- Open Broadcaster Software
- Real Time Messaging Protocal Server

Challenges

1. Navigate
2. Auth
3. forms
4. CRUD in react/redux
5. Error handling

## Navigate(React Router)

- 安裝 package
  - react-router: core navigation lib, we won't install this manually
  - __react-router-dom__: navigation for dom-based apps
  - react-router-native: navigation for react-native apps
  - react-router-redux: binding between redux and react router

```cmd
npm install --save react-router-dom
```

- 使用 react-router-dom

```js
import { BrowserRouter, Route } from 'react-router-dom';

<BrowserRouter>
    <div>
        <Route path="/" exact component={PageOne}/>
        <Route path="/pagetwo" component={PageTwo}/>
    </div>
</BrowserRouter>

```

### route 規則

- 重複兩次的相同的 path 的話, 就會有兩個 component
- 如果path '/' 沒有 exact 的話, '/pagetwo' url 會有 PageOne 和 PageTwo 兩個 component, 因為 '/' 和 '/pagetwo' 皆符合
- exact === exact={true}
- 

- 不要用傳統的 html anchor tag的方式做navigate
  - 會重新load 一次 index.html, 和所有東西

```js
<a href="/pagetwo">Link</a>
```

- 用 Link 取代 anchor tag

```js
import { Link } from 'react-router-dom';

<Link to="/pagetwo">Navigate to page Two</Link>
```

### 三種 router

1. BrowserRouter
  - localhost:3000 __/pagetwo__
2. HashRouter
  - localhost:3000/# __/pagetwo__
3. MemoryRouter
  - don't use the URL to track navigation
  - URL 不會變

- 在 react development server 裡面, 如果沒有符合 URL的檔案, 都是回傳 index.html, 而非像傳統的server回傳 404

### Always visible components

- 放在 BrowserRouter 外面的話
  - 如果在 Header 裡面有用 Link, 會有 錯誤跑出來: should not use <Link> outside a <Router>
```js
<Header />
<BrowserRouter>
</BrowserRouter>
```

- 改成下面這樣

```js
<BrowserRouter>
  <div>
      <Header/>
      <Route path="/" exact component={StreamList}/>
  </div>
</BrowserRouter>
```

## OAuth-based Authentication

- [Google scopes](https://developers.google.com/identity/protocols/oauth2/scopes)
  - [Sign In](https://developers.google.com/identity#google-sign-in)


### OAuth client ID

1. 建立新project
2. 設定 OAuth 同意畫面
3. 建立 OAuth 2.0 用戶端ID
4. 安裝 Google's API library
  - 在 index.html 的 head tag 裡面加入 script
```html
<script src="https://apis.google.com/js/api.js"></script>
```
  - 在 console 可以打 "gapi"
  - 把下面這些放在 GoogleAuth component 中

```cmd
> gapi
> gapi.load('client:auth2')
> gapi
> gapi.client.init({ clientId: 'YOUR_CLIENT_ID'})
> gapi.auth2.getAuthInstance() // 取得 'auth' object
> gapi.auth2.isSignedIn.get() 
> gapi.auth2.getAuthInstance().signOut() // 登出
```

- 可以參考 GoogleAuth.js

### 結合 Redux

- 可以在 app 其他地方知道 Auth State
- 把一些動作放到 action creators

- 安裝 package
  - npm install --save redux react-redux

```js
// actions
export const signIn = () => {
    return{
        type: 'SIGN_IN'
    };
};
```

```js
// GoogleAuth.js 使用方
    
onAuthChange = (isSignedIn) => {
    // this.setState({ isSignedIn: this.auth.isSignedIn.get() });
    if (isSignedIn) {
        this.props.signIn();
    } else {
        this.props.signOut();
    }
};

const mapStateToProps = (state) => {
    return { isSignedIn: state.auth.isSignedIn }
};

export default connect(
    mapStateToProps, 
    { signIn, signOut }
)(GoogleAuth);

```

### 紀錄 user ID

```cmd
gapi.auth2.getAuthInstance().currentUser
gapi.auth2.getAuthInstance().currentUser.get().getID()
```

## Redux Forms

### Redux Dev tools

- 觀看 redux store 裡面的資料
- [Redux-devtools-extension](https://github.com/zalmoxisus/redux-devtools-extension)


```js
import { createStore, applyMiddleware, compose } from 'redux';

const composeEnhancers = window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__ || compose;
const store = createStore(
    reducers,
    composeEnhancers(applyMiddleware())(
);

```

- localhost:3000?debug_session=<some_string>
  - save all data in redux store between refreshes of the page
  - 可以取名字(debug_session), 然後儲存一定的動作

### 安裝 package

- redux-form
  - npm install redux-form --legacy-peer-deps
  - 會幫忙處理建立 reducers, 還有 mapStateToProps, action creator
  - 專心在處理 component 中的 __props__ 和 __handler__

- [Redux Form-example](https://redux-form.com/8.3.0/examples/simple/)
  - Synchronous Validation
  - Wizard form

- 在 reducer 中加入 redux-form 會幫我們產生的 reducer

```js
// \src\reducers\index.js
// 順便用 as 改名, 避免混淆
import { reducer as formReducer } from 'redux-form'

export default combineReducers({
    auth: authReducer,
    form: formReducer
});
```

### Creating Forms

- 在 StreamCreate.js

```js
// Field 會是在畫面顯示的 component
// refuxForm 像是 react-redux 的 connect
import { Field, reduxForm } from 'redux-form'

export default reduxForm({
    form: 'streamCreate'
})(StreamCreate);
// 加了之後, 在 this.props 就會多很多屬性
```

- Field 裡面的 component 會收到很多props, 手動將 value 和 onChange 連結

```js
<Field name="title" component={this.renderInput}/>

renderInput(formProps) {
  console.log(formProps)
  return (        
    <input 
      onChange={formProps.input.onChange} 
      value={formProps.input.value}
    />
    // 等同於
    <input {...formProps.input}/> 
  );
}
```

### Form Submission

- this.props 裡面, 有一個 redux-form 提供的 __handleSubmit__ property

```js
onSubmit(event) {
  event.preventDefault();
}


// 之前的方式
<form onSubmit={this.onSubmit}>
</form>

// 使用 redux-form, handleSubmit
<form onSubmit={this.props.handleSubmit(this.onSubmit)}>
</form>

// handleSubmit, 也會接收到 event, 然後會自動call event.preventDefault()
// redux-form 會接受到的參數是 <form> 裡面的 field
onSubmit(formValues) {
    console.log(formValues.title);
    console.log(formValues.description);
}
```

### Validation of Form Inputs

- 在 component 外面宣告 validate function
- key 的名稱要跟 Field 裡面的 name 名稱一樣

```js
const validate = (formValues) => {
    const errors = {};

    if (!formValues.title) {
        // only ran if user did not enter a title
        errors.title = 'You must enter a title!';
    }

    if (!formValues.description) {
        errors.description = 'You must enter a description.';
    }

    return errors;
};

// 連結 validate function
export default reduxForm({
    form: 'streamCreate',
    validate: validate
})(StreamCreate);

// 印出 error message(存在 meta.error)
renderInput({ input, label, meta }) {
  <div>{meta.error}</div>
};

```

## REST-based

### API Server

- [json-server](https://www.npmjs.com/package/json-server)
- REST-ful Conventions: standardized system for designing API's
- 在 \streams\ 資料夾底下

```cmd
> mkdir api
> cd api
> npm init
> enter到底
> npm install --save json-server
> 建立 db.json
```

- 刪除 package.json 裡面的 default scripts, 改成:

```json
{
  "scripts": {
    "start": "json-server -p 3001 -w db.json"
  }
}
```

- 執行指令, 開啟 json-server
  - http://localhost:3001/streams

```cmd
> npm start
```

### Create object in Action creator

- 安裝 axios 和 redux-thunk
  - npm install --save axios redux-thunk
- 建立 \src\apis\streams.js

```js
// POST
export const createStream = (formValues) => async (dispatch) => {
    streams.post('/streams', formValues);
};
```

- 在 StreamCreate 裡面, 利用 connect 使用 action

```js
export default connect()(
  reduxForm({
    form: 'streamCreate',
    validate: validate
  })(StreamCreate)
);


// 比較乾淨的寫法
const formWrapped = reduxForm({
    form: 'streamCreate',
    validate: validate
})(StreamCreate);

export default connect(null, { createStream })(formWrapped);

// form-onSubmit
onSubmit(formValues) {
    this.props.createStream(formValues);
}
```

### Array-based approach

```js
const streamReducer = (state = [], action) => {
  switch(action.type) {
    case EDIT_STREAM:
      return state.map(stream => {
        if (stream.id === action.payload.id) {
          return action.payload;
        }
        else {
          return stream;
        }
      }); 
    default:
      return state;
  }
};
```

### Object-based approach

- 不再是用 array 存放資料, 而是用 {} object
- object 裡面, key 是 id, value 是 該id 的 stream object

```js
const streamReducer = (state = {}, action) => {
  switch(action.type) {
    case EDIT_STREAM:
      const newState = { ...state };
      newState[action.payload.id] = action.payload;
      return newState;

      // key interpolation syntax, 功用跟上面一模一樣
      return { ...state, [action.payload.id]: action.payload } 
    default:
      return state;
  }
};
```

### mapKeys in lodash

```js
const colors = [
  { hue: 'green' },
  { hue: 'yellow' },
  { hue: 'blue' }
];

_.mapKeys(colors, 'hue');

// mapKeys 會建立一個 object 如下
{
  "green": { "hue": "green" },
  "yellor": { "hue": "yellow"},
  "blue": { "hue": "blue" }
}

```

### Authentication

- 辨別 stream 是哪個 user 建的

```js
// 在 action 裡面利用 getState 取得 ID

export const createStream = (formValues) => async (dispatch, getState) => {
    const { userId } = getState().auth;    
    
    const response = await streams.post('/streams', { ...formValues, userId });

    dispatch({ type: CREATE_STREAM, payload: response.data });
};
```

### Navigation to other page

- Intentional Navigation

```js
import { Link } from 'react-router-dom';

renderCreate() {
  if (this.props.isSignedIn) {
    return (
      <div style={{ textAlign: 'rright'}}>
        <Link to="/streams/new" className="ui button primary"> 
          Create Stream
        </Link>
      </div>
    );
  } 
}
```

- Programmatic Navigation 
  - BrowserRouter 會把 history 當作 props 傳給 Route 生成的 component
  - 在 component 裡面去做URL 切換比較簡單
  - 但現在是要在 action creator 裡面做
    1. (not ideal) 在 component 中, 也把 history object 傳給 action creator
    2. 自己另外建一個 file(取代 BrowserRouter) 來存放 history object

```js
// history.js
import { createBrowserHistory } from 'history'; 
export default createBrowserHistory();

// App.js
<Router history={history}>
</Router>
```

```js
// 在程式中做 navigation 
history.push('/')
```

### edit stream

1. Selection Reducer
  - 可以參考 songs project: selectedSongReducer
2. URL-based selection


### wildcard

```js
<Route path="/streams/edit/:id" exact component={StreamEdit}/>

<Link to={`/streams/edit/${stream.id}`} className="ui button primary">
  Edit
</Link>
```

- 在 StreamEdit component 的 props object 裡面 會有 history, location, match . 因為 這個component 是從 Route render 出來的

```js
// props.match.params.id 可以取得 URL 上的參數
const mapStateToProps = (state, ownProps) => {
    return { stream: state.streams[ownProps.match.params.id] };
};
```

### component isolation 

- 如果URL直接輸入的話, 沒有 fetch streams, 所以stream 會是 undefined
- With React-Router, each component needs to be designed to work in isolation(fetch its own data!)

### initial values for reduxForm

```js
return (
    <div>
      <h3>Edit a Stream</h3>
      <StreamForm
          initialValues={this.props.stream} 
          onSubmit={this.onSubmit}/>
    </div>
);

// 如果 initial values 直接用 this.props.stream
// 可能會有一些不想要修改的 property 也一起傳入 (ex: id, userId)

// 第一種解法: {{ title: this.props.stream.title }}

// 第二種解法: 用 lodash 的 pick
initialValues={_.pick(this.props.stream, 'title', 'description')} 
```

### Edit: PUT vs, PATCH

```js
this.props.editStream(this.props.match.params.id, formValues);

// PUT: update all properties of a record

// PATCH: update some properties of a record
```

