
#### Create a React app

```cmd
npm --version
npm install -g create-react-app
npx create-react-app react-task-tracker
react-task-tracker % code .
```

#### Files & folders

- npm start
  - Starts the development server.
- npm run build
  - Bundles the app into static files for production.
- npm test
  - Starts the test runner.
- npm run eject
  - Removes this tool and copies build dependencies, configuration files and scripts into the app directory. If you do this, you can’t go back!

- package.json 可以看到 有安裝
  - "react": "^17.0.2",
  - "react-dom": "^17.0.2",
  - "react-scripts": "4.0.3",

```cmd
cd react-task-tracker
npm start // start the dev server, localhost:3000
```

- .\public\index.html 是首頁內容

#### JSX

```js
function App() {
  const name = 'Brad'

  return (
    <div className="container">
      <h1>Hello From React</h1>
      <h2>Hello {name}</h2>
    </div>
  );
}
```

#### Create a component

- 安裝 extensions: ES7 React/Redux/GraphQL/React-Native snippets
- hotkey: rafce, to create arrow function
- 建立新檔案: Header.js, 並在 App.js 引入

```js
import Header from './components/Header'

function App() {
  return (
    <div className='container'>
      <Header />
    </div>
  );
}

export default App;
```

#### Component Pros

- 在使用方(App.js)
```js
<Header title='Hello'/>
```

- 在 Header.js
```js
const Header = (props) => {
    return (
        <header>
            <h1>{props.title} Task Tracker</h1>
        </header>
    )
}
```

- default props

```js
Header.defaultProps = {
    title: 'Default Header: '
}
```

- PropTypes, 如果傳入的不是該型別會有警告

```js
Header.propTypes = {
    title: PropTypes.string,
}
```

#### Styling

- use .css (index.css)

```js
<header className='header'>
  <h1>{title}</h1>
  <button className='btn'>Add</button>
</header>
```

- use Style Component

- use direct css in javascript

```js
<h1 style={{color: 'red', backgroundColor: 'black'}}>{title}..Task Tracker</h1>
```

```js
<h1 style={headingStyle}>{title}..Task Tracker</h1>

const headingStyle = {
    color: 'green', 
    backgroundColor: 'black'
}
```

#### Button component

```js
import Button from './Button'

<Button color='green' text='Add'/>
```

```js
const Button = ({color, text}) => {
    return (
        <button style={{backgroundColor: color}} 
            className='btn'>{text}</button>
    )
}

Button.defaultProps = {
    color: 'steelblue'
}

Button.propTypes = {
    text: PropTypes.string,
    color: PropTypes.string
}


export default Button
```

#### Events

```js
const onClick = (e) => {
    console.log(e)
}

return (
    <button 
        onClick={onClick} 
        style={{backgroundColor: color}} 
        className='btn'>
        {text}
    </button>
)
```


#### Tasks component

- 建立Tasks.js

#### Create a list with .map()

```js
<>
  {tasks.map((task) => (
    <h3 key={task.id}>{task.text}</h3>
  ))}  
</>
```

#### State & useState Hook

- state 是 oneway data?

- 用 context API, redux 來處理 state

```js
    import { useState } from 'react'

    const [tasks, setTasks] = useState([
        {
            id: 1,
            text: 'Doctors Appointment',
            day: 'Feb 5th at 2:30pm',
            reminder: true
        },
        {
            id: 2,
            text: 'Meeting at School',
            day: 'Feb 6th at 1:30pm',
            reminder: true
        },
        {
            id: 3,
            text: 'Food Shopping',
            day: 'Feb 5th at 2:30pm',
            reminder: false
        }
    ])
```

#### Global state

- 把 tasks state 放到 App.js 裡面

#### Task Component

- 建立 Task.js

#### Icons with react-icons

- 安裝 react-icons packages

```cmd
npm i react-icons
```

- 安裝完後 package.json 會增加

```js
import { FaTimes } from 'react-icons/fa'

<h3>
  {task.text} 
  <FaTimes style={{color: 'red', cursor: 'pointer'}}/>
</h3>
```

#### Delete task & prop driling

- 增加一個 onDelete 的 props 傳下去

- App.js

```js
const deleteTask = (id) => {
  console.log('delete', id);
};
```

- Task.js

```js
<FaTimes onClick={() => onDelete(task.id)}/>
```

- 實際刪除的動作

```js
const deleteTask = (id) => {
  // console.log('delete', id);
  setTasks(tasks.filter((task) => task.id !== id));
};
```

#### Optional message if no tasks

- 用條件來決定要顯示的元件內容

```js
{ tasks.length > 0 
  ? <Tasks tasks={tasks} onDelete={deleteTask}/>
  : 'No tasks to show'
}
```

#### Toggle reminder & conditional styling

- 增加 onToggle event handler, 像onDelete

- 如果 id 相同, task 設定成, 保留 task 內容(...task), 但是 reminder 換掉
- 如果 id 不同, 維持 task

```js
  const toggleReminder = (id) => {
    // console.log('toggleReminder', id);
    setTasks(
      tasks.map(
        (task) => task.id === id 
        ? { ...task, reminder: !task.reminder} 
        : task
      )
    )
  };
```

- 利用條件, 修改class名稱, 用 `` 包起來

```js
<div className={`task ${task.reminder ? 'reminder' : ''}`}>

</div>
```

#### Add Task Form

- 建立 AddTask.js

#### Form input state (controlled components)

```js
const [text, setText] = useState('')

<input 
  type='text' 
  placeholder='Add Task' 
  value={text} 
  onChange={(e) => setText(e.target.value)}>    
</input>
```

#### Add task submit

```js
// in App.js
// Add Task
const addTask = (task) => {
    // console.log(task);
    const id = Math.floor(Math.random() *10000) + 1;
    const newTask = { id, ...task }
    setTasks([...tasks, newTask])
}

<AddTask onAdd={addTask} />

// in AddTask.js
const AddTask = ({onAdd}) => {
    const onSubmit = (e) => {
        e.preventDefault()

        if (!text) {
            alert('Please add a task')
            return
        }

        onAdd({text, day, reminder})

        setText('')
        setDay('')
        setReminder(false)
    }

    <form onSubmit={onSubmit}>
        ...
    </form>
}

```

#### showAddTask state

```js
const [showAddTask, setShowAddTask] = useState(true);
// 決定要不要顯示 AddTask component
{showAddTask && <AddTask onAdd={addTask} />}
```

#### Button toggle

```js
<Header onAdd={()=>setShowAddTask(!showAddTask)}/>
```

#### Build for production

```cmd
// 之前是 npm start

// 現在是
npm run build

// 這會產生一個 "build" 的資料夾
// build 就是要 release/deploy 的東西

// 安裝 serve
npm install -g serve

// 開在 http://localhost:8000
serve -s build -p 8000
```

#### JSON Server

- mock backend
```cmd
npm install json-server

json-server --watch db.json
```

- 在 package.json 裡面增加 scripts: server
```json
"scripts": {
  "server": "json-server --watch db.json --port 5000"
},
```

- 就可以用 npm run server 來下指令
```cmd
npm run server
// http://localhost:5000/tasks 可以看到新增的資料

npm start // 原本的也要開
```

#### useEffect Hook & Fetch tasks from server

```js
import { useEffect } from 'react'

  useEffect(() => {

    const getTasks = async () => {
      const tasksFromServer = await fetchTasks()
      setTasks(tasksFromServer)
    }

    getTasks();

    return () => {
      // cleanup
    }
  }, [])

  // Fetch tasks
  const fetchTasks = async() => {
    const res = await fetch('http://localhost:5000/tasks');
    const data = await res.json();
    // console.log(data);
    return data;
  }

```


#### Delete task from server
#### Add task to server
#### Toggle reminder on server

#### Routing, footer & about

- npm i react-router-dom

```js

import { useLocation } from 'react-router-dom'

{ 
  location.pathname === "/" && 
  <Button />
}
```


