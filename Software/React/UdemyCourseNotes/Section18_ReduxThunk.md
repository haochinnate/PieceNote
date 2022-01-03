# Async Actions with Redux Thunk

- 內容在 \blog 中

- understand the purpose of reducers
- understand making API requests with Redux
- understand the purpose of 'redux-thunk'

## 安裝 packages

```cmd
npm install --save redux react-redux axios redux-thunk
```

- redux: the redux library
- react-redux: integration layer between react and redux
- axios: helps us make network requests
- redux-thunk: middleware to help us make requests in a redux application

## fetch data in Redux

- [JSONPlaceholder API](jsonplaceholder.typicode.com)

1. component gets rendered onto the screen
2. componentDidMount 有被呼叫
3. 從 componentDidMount 呼叫 action creator

```js
componentDidMount() {
    this.props.fetchPosts();
}

export default connect(
    null, 
    { fetchPosts: fetchPosts }
)
(PostList);

```

4. action creator 呼叫 API request
   - __action creators__ 只能回傳 plain JS objects
   - 用了 async & await 後, Babel compile 實際的 code 並不是回傳 plain JS objects
   - 就算把 async & await 拿掉, 也會有問題, 因為 reducers 在 處理 action 的時候, 可能還沒有取得 response, 所以沒有 data

5. API 回傳 data
 
```js
export default axios.create({
    baseURL: 'http://jsonplaceholder.typicode.com'
});
```

```js
export const fetchPosts = async () => {
    // Bad approach
    const response = await jsonPlaceholder.get('/posts');
    
    return {
        type: 'FETCH_POSTS',
        payload: response
    };
};
```

> Error: Actions must be plain objects. Instead, the actual type was: 'Promise'. You may need to add middleware to your store setup to handle dispatching other values, such as 'redux-thunk' to handle dispatching functions.

6. action creator 回傳在 payload property 帶有 data 的 action  
7. 有些 reducers 會 watch action, 將 data 從 payload 取出
8. state object 接收 data, react 要 rerendered component

## Asynchronous action creator

- 需要時間來 dispatch an action
- 利用 middleware: redux-thunk
- dispatch 跟 reducers 中間, 加了 __Middleware__
- Middleware 可以針對 actions 做 __STOP__, __MODIFY__, 或其他動作
- Redux-Thunk 讓 Action creator 可以回傳 "action objects" 或 "functions"
  - action objects -> 傳給 reducer
  - function -> 會有 dispatch getState props, 之後可以 __手動呼叫 dispatch__ 得到 new action, 然後才 dispatch 這個 new action

```js
// wireup thunk as middleware
import { createStore, applyMiddleware } from 'redux';
import thunk from 'redux-thunk'

const store = createStore(reducers, applyMiddleware(thunk));
<Provider store={store}>
    <App />
</Provider>

```

- 在 \actions\index.js (action creator) 那邊

```js
export const fetchPosts = () => {
    return async function(dispatch, getState) {
        const response = await jsonPlaceholder.get('/posts');

        dispatch({ type: 'FETCH_POSTS', payload: response })
    };
};

// 簡寫成這樣也可以
return async (dispatch) => {
    // ...
}

// 還能再簡寫成 
const fetchPosts = () => async dispatch => { };
```

## Rules of Reducers

- Must return any value besides 'undefined'
  - 一定要給初始值, null 也可以
- Produces 'state' for data to be used inside of your app using only previous state and the action
  - reducers 會私底下被 call 一次

```js
selectedSongReducer(undefined, { type: 'jeriejirj'})
```
- Must not return react 'out of itself' to decide what value to return(reducers are pure)
  - reducers 應該要只處理 previous state(data) 和 action, 來決定要回傳什麼

```js
export default (state, action) => {
    // bad
    return document.querySelector('input');

    // bad
    return axios.get('/posts')

    // good: state + action 
    return 
}
```

- MISLEADING >> Must not mutate its input 'state' argument
  - 重點不是不能改, 而是如果資料維持原樣的話, 不會觸發後續的動作, 不會更新

```js
// mutating:
const color = ['red', 'green']
colors.push('purple')
colors.pop()
colors[0] = 'pink'

const profile = { name: 'Alex' }
profile.name = 'Sam'
profile.age = 30

// BAD!
state[0] = 'sam'
state.name = 'sam'
state.age = 30

```

## Safe State Updates in Reducers 

```js
// removing an element from an array
state.filter(element => element !== 'target')

// adding an element to an array
[...state, 'new element']

// replacing an element in an array
state.map(el => el === 'target' ? 'new value' : el)

// updating a property in an object
{ ...state, name: 'Sam' }
// { name: 'sam', ...profile }// 這個不會生效

// adding a property to an object 
{ ...state, age: 30 }

// removing a property from an object
{ ...state, age:undefined }
// lodash
_.omit(state, 'age')
```

## 實作 reducer

- 看 postReducer.js

## post user id 對照 user

```js
// 方法1: fetch 全部 users (Too Easy!, not realistic)

// 方法2: 根據每個 post 的 userID 去 fetch user

// 從 post 中得到的 userId 傳入 UserHeader component
<UserHeader userId={post.userId}/>

// UserHeader 有 fetchUser action 可以藉由 id 取得 user 詳細資料
this.props.fetchUser(this.props.userId);

export default connect(mapStateToProps, { fetchUser })(UserHeader);


// 為了避免傳入全部的 users 造成時間浪費
// 不要寫: return { users: state.users };
// 在 mapStateToProps 做 pre-calculation
const mapStateToProps = (state, ownProps) => {
    return { 
        user: state.users.find(user => user.id === ownProps.userId)
    };
};

// 後續在 component 中可以取出來
const { user } = this.props;
// or 
this.props.user
```

- 利用 ownProps 取得 該 component 的 props

## 避免重複 request 相同的資料 

- fetchUser 會因為 post 數量重複呼叫10次

### 解法 1: 使用memoize function

- [Lodash-memoize](https://lodash.com/docs/#memoize)

```cmd
> npm install --save lodash
```

- 簡單範例

```js
function getUser(id) {
    fetch(id);
    return 'Make a request!';
}

getUser(2); // 會送 request
getUser(2); // 會送 request
getUser(4); // 會送 request

// 把 getUser function 包起來
const memoizedGetUser = _.memoize(getUser)

memoizedGetUser(3) // 會送 request
memoizedGetUser(3) // 同參數, 第二次開始就不會送 request
```

- 實際在 project 裡面, memoize out side the action

```js
export const fetchUser = (id) => dispatch => {
    _fetchUser(id, dispatch);
};

const _fetchUser = _.memoize(async (id, dispatch) => {
    const response = await jsonPlaceholder.get(`/users/${id}`);

    dispatch({ type: 'FETCH_USER', payload: response.data });
});
```

### 解法 2: 建一個 fetchPostsAndUsers 的 action

```js
// 不能直接 call fetchPosts()
// 需要 dispatch其結果 
await dispatch(fetchPosts())

// 利用第二個參數 getState 來取得資料
async (dispatch, getState) => { }
const userIds = _.uniq(_.map(getState().posts, 'userId'))
userIds.forEach(id => dispatch(fetchUser(id)));
```


