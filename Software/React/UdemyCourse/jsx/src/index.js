// Import the React and ReactDOM libraries
import React from 'react';
import ReactDOM from 'react-dom';


function getButtonText() {
    return 'Click on me!';
}

// Create a react component
const App = () => {
    const buttonText = 'Click Me!'; 
    // const buttonText = {text: 'click me'}; 

    // return <div>Hi there!</div>;
    // 多行的排版
    return (
        <div>
            <label className="label" htmlFor="name">
                Enter name:
            </label>
            <input id="name" />
            <button style={{ backgroundColor: 'blue', color: 'white' }}>
                {/* Submit */}
                {buttonText}
                {/* {getButtonText()} */}
            </button>
        </div>
    );
};


// Take the react component and show it on the screen
ReactDOM.render(
    <App />,
    document.querySelector('#root')
);
