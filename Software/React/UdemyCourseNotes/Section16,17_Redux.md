# Redux

- State management library
- Makes creating complex applications easier
- Not required to create a React app!
- Not explicitly designed to work with React

## Redux Cycle

1. Action Creator
2. Action 
3. Dispatch
4. Reducers
5. State

## Analogy for Redux

- Insurance company
  - Form to Receiver
  - Departments
    - Claims history
    - Policies
    - Accounting
  - All Department Data
  - Management team!

- Form
  - Type: CREATE CLAIM, CREATE POLICY, DELETE POLICY 
  - Payload

## Mapping to Redux

1. Action Creator -> Person dropping off the form
2. Action -> the form

```js
// People dropping off ａ form (Action Creator)
const createPolicy = (name, amount) => {
  // Action (a form in analogy)
  return { 
    type: 'CREATE_POLICY',
    payload: {
      name: name,
      cash: amount
    }
  };
};

const deletePolicy = (name) => {
  return {
    type: 'DELETE_POLICY',
    payload: {
      name: name      
    }
  };
};

const createClaim = (name, amountOfMoneyToCollect) => {
  return {
    type: 'CREATE_CLAIM',
    payload: {
      name: name,
      amountOfMoneyToCollect: amountOfMoneyToCollect
    }
  };
};
```

3. Dispatch -> form receiver

```js
// Dispatch is part of Redux library
```

4. Reducers -> Departments

```js
// Reducers (Departments)
const claimsHistory = (oldListOfClaims = [], action) => {
  
  // when first time be called, oldListOfClaims may not created 
  // so use oldListOfClaims = []
  
  if (action.type === 'CREATE_CLAIM') {
    // we care about this action (Form)
    // ...: 拿所有的 items, 然後加上後面的item 形成一個新的 array 
    // 在 reducers 裡面要修改東西時, 都是 return 一個新的 array或 新的 object, 而不是修改原本的
    return [...oldListOfClaims, action.payload];
  }
  
  // we don't care the actions (form)
  return oldListOfClaims;
};

const accounting = (bagOfMoney = 1000, action) => {
  if (action.type === 'CREATE_CLAIM') {
    return bagOfMoney - action.payload.amountOfMoneyToCollect;
  } else if (action.type === 'CREATE_POLICY') {
    return bagOfMoney + action.payload.cash;
  }
  
  return bagOfMoney;
}

const policies = (listOfPolicies = [], action) => {
  if (action.type === 'CREATE_POLICY') {
    return [...listOfPolicies, action.payload.name];
  } else if (action.type === 'DELETE_POLICY') {
    return listOfPolicies.filter(name => name !== action.payload.name);
  }
  
  return listOfPolicies;
};
```



5. State -> compiled deparment data

```js
// state 就是下面的 store, 裡面存放所有的 data
```

- Store: essentially the assembly of a collection of different reducers and action creators

```js
// 結合上面的 Action creators 和 Reducers

const { createStore, combineReducers } = Redux;

// 每一個 reducer 就是一個 function
// combineReducers: wire up這些 functions together
// 把所有 reducers 結合起來 
// 因為有 key name, 所以在後面 store.getState() 才會有那些值
const ourDepartments = combineReducers({
  accounting: accounting,
  claimsHistory: claimsHistory,
  policies: policies
});

// store 表示整個 Redux application
const store = createStore(ourDepartments);

// 用 action creator 建立 action, 
const action = createPolicy('Alex', 20);
console.log(action);

// store dispatch action, 會分配到對應的 reducers 

store.dispatch(action);

// 建立action 跟 dispatch 可以寫在同一行
store.dispatch(createPolicy('Bob', 30));
store.dispatch(createPolicy('Jim', 40));

store.dispatch(createClaim('Alex', 120));
store.dispatch(createClaim('Jim', 50));

store.dispatch(deletePolicy('Bob'));

// 用 getState() 取得 目前 store 的情況
console.log(store.getState());

// redux 只能用 action, reducers 來改變 store 的狀態
// store.state.accounting - 100 是做不到的

```

# Section 17: React-Redux

- 範例: \reactplayground\songs
- React-Redux: Gets React and Redux to work together
- install redux and react-redux

```cmd
> npm install --save redux react-redux
```

- Reducers
  - Song list reducer
  - Selected song reducer
- Action Creators
  - Select Song

- 使用 react-redux 要建立兩個新的 components
  1. Provider
    - Redux 建立的 store 會包含application 需要的 reducers 和 state
    - 這個 store 會當作參數傳給 Provider
    - Provider 比 App component 還上一階 => show App inside Provider
  2. Connect: communicate with the 'Provider'
    - Song List 需要知道 store 裡面的資訊, 所以在Song List 上面建立了一個 Connect(Connect 會包住 SongList)
    - Connect tag/component 是一個特別的 component, 它是藉由 __context system__ 來跟 Provider 溝通
    - Connect 去跟 Provider 說有變更的時候 需要資料, Provider 傳給 Connect 後, Connect 再傳給 SongList
    - 告訴 Connect, Song List 想要用哪一個 action creator
    - 特定的 action creator 和 state 會當作 props 傳給 SongList
- Store -> __Provider__ -> App -> __Connect__ -> SongList/SongDetail


## file organization

- src
  - \actions: action creators
  - \components: files related to components
  - \reducers: reducers
  - index.js: setup both react and redux

```js
// 在 \actions 資料夾底下建立 index.js
// 原先是用下面來import 
import actions from '../actions/index';

// 用 index.js 可以變成
import actions from '../actions';
```

## action creator

```js
// 同一個 js 會有很多 function, 所以直接掛 export 
export const selectSong = (song) => {
    // return an action
    return {
        type: 'SONG_SELECTED',
        payload: song
    }; 
}; 

// import 使用變成
import { selectSong } from "../actions";
// export default selectSong 的話
// import 不需要 {} 
```

## reducers

```js
import { combineReducers } from 'redux';

const songsReducer = () => {
    return [
        { title: 'just a song', duration: '4:05'},
        { title: 'Macarena', duration: '2:30'},
        { title: 'All Star', duration: '3:15'},
        { title: 'Numb', duration: '1:45'}
    ];
};


const selectedSongReducer = (selectedSong = null, action) => {
    if (action.type === 'SONG_SELECTED') {
        return action.payload;
    }

    return selectedSong;
};

// 直接在 \src\reducers\index.js 裡面 combine 起來
// 並 export 出去
export default combineReducers({
    songs: songsReducer,
    selectedSong: selectedSongReducer
});
```

## 在 index 中整合 Provider & store

```js
import { Provider } from 'react-redux';
import { createStore } from 'redux';
import reducers from './reducers'

// create instance of "Provider", and pass in "store" as props
ReactDOM.render(
  <Provider store={createStore(reducers)}>
    <App />,
  </Provider>, 
  document.querySelector('#root')
);
```

## Connect component

- 所以在 react-redux 裡面, 通常不是直接操作 store, 而是透過 Connect

```js
// 在 SongList.js 中
import { connect } from 'react-redux';

export default connect()(SongList);

// function connect() {
//   return function() {
//     return 'Hi there!';
//   }
// }
// connect()()

```

## mapStateToProps

```js
// 想要從 Provider 拿到 redux store 裡面的資料
// 相當於 設定 class components 的 props 為
// this.props === { songs: state.songs }

const mapStateToProps = (state) => {
  return { songs: state.songs };
};

export default connect(mapStateToProps)(SongList);

// 在 SongList class component 中
// props 的值會有
// 1. songs
// 2. dispatch
```

## 呼叫 action creator

```js
import { selectSong } from '../actions';

export default connect(mapStateToProps, {
    selectSong: selectSong
    // 新語法的話 只寫 selectSong 也可以
})(SongList);

// this.props 就會有 selectSong

// 使用時, 在 button 的 onClick 呼叫
onClick={() => this.props.selectSong(song)}>

```

- Redux does not automatically detect action creators being called
- Redux does not automatically detect a function returning an object that is an 'action'

```js
selectSong(); // 這樣呼叫只是單純的呼叫一個 function, 跟 Redux 無關
// action creator 要有效, 需要帶入 store.dispatch

// connect() 會將作為參數的 function, 包成 新的 JS function, 然後呼叫 dispatch
```

## function component 的情況

- 參考 SongDetail.js
