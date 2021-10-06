// import logo from './logo.svg';
// import './App.css';
import { useState, useEffect } from 'react'
import { BrowserRouter as Router, Route } from 'react-router-dom'
import Header from './components/Header'
import Footer from './components/Footer'
import Tasks from './components/Tasks'
import AddTask from './components/AddTask'
import About from './components/About'

function App() {
  const name = 'Brad'

  const [showAddTask, setShowAddTask] = useState(true);

  // app level state
  const [tasks, setTasks] = useState([])

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

   // Fetch task
   const fetchTask = async (id) => {
    const res = await fetch(`http://localhost:5000/tasks/${id}`);
    const data = await res.json();
    // console.log(data);
    return data;
  }

  // Add Task
  const addTask = async (task) => {

    const res = await fetch(`http://localhost:5000/tasks`, {
      method: 'POST', 
      headers: {
        'Content-type': 'application/json'
      },
      body: JSON.stringify(task)
    })

    const data = await res.json();

    setTasks([...tasks, data])
    // console.log(task);
    // const id = Math.floor(Math.random() *10000) + 1;
    // const newTask = { id, ...task }
    // setTasks([...tasks, newTask])
  }

  // Delete task
  const deleteTask = async (id) => {
    // console.log('delete', id);
    await fetch(`http://localhost:5000/tasks/${id}`, {
      method: 'DELETE'
    })

    setTasks(tasks.filter((task) => task.id !== id));
  };

  // Toggle reminder
  const toggleReminder = async (id) => {
    // console.log('toggleReminder', id);
    const taskToToggle = await fetchTask(id);
    const updTask = { ...taskToToggle, reminder: !taskToToggle.reminder }

    const res = await fetch(`http://localhost:5000/tasks/${id}`, {
      method: 'PUT', 
      headers: {
        'Content-type': 'application/json'
      },
      body: JSON.stringify(updTask)
    });

    const data = await res.json();

    setTasks(
      tasks.map(
        (task) => task.id === id 
        ? { ...task, reminder: data.reminder} 
        : task
      )
    )
  };

  return (
    <Router>
      <div className='container'>
        {/* <h1>Hello From React</h1> */}
        {/* <h2>Hello {name}</h2> */}
        {/* <Header title={1}/> */}
        {/* <Header/> */}
        <Header title='Task Tracker' onAdd={()=>setShowAddTask(!showAddTask)}
          showAdd={showAddTask}/>
       
        <Route path="/" exact render={(props) => (
            <>
              {showAddTask && <AddTask onAdd={addTask} />}

              { tasks.length > 0 
              ? (<Tasks tasks={tasks} onDelete={deleteTask}
                onToggle={toggleReminder}/>)
              : ('No tasks to show')
              }
            </>
        )} />
        <Route path="/about" component={About} />
        <Footer/>
      </div>
    </Router>
    
  );
}

export default App;
