import React  from 'react'
import ReactDOM from 'react-dom'
import SeasonDisplay from './SeasonDisplay'
import Spinner from './Spinner'
import { Component } from 'react'

// const App = () => {
//     window.navigator.geolocation.getCurrentPosition(
//         // success callback
//         (position) => console.log(position),

//         // failure callback
//         (err) => console.log(err)
//     );


//     return (
//       <div>
//           {/* <SeasonDisplay/> */}
//           Latitude: 
//       </div>
//     );
//   };

class App extends Component {

    // constructor(props) {
    //     super(props);

    //     // THIS IS THE ONLY TIME we do direct assignment to this.state
    //     this.state = {latitude: null, errorMessage: ''};
    // }

    state = { latitude: null, errorMessage: '' };

    componentDidMount() {
        console.log('rendered, componentDidMount');

        window.navigator.geolocation.getCurrentPosition(
            // success callback
            (position) => {
                // console.log(position)
                this.setState({ latitude: position.coords.latitude });
            },
    
            // failure callback
            (err) => { 
                // console.log(err)
                this.setState({ errorMessage: err.message })
            }
        );

        console.log('componentDidMount End');
    }

    componentDidUpdate() {
        console.log('rerendered, componentDidUpdate');
    }

    // helper method
    renderContent() {
        if (this.state.errorMessage && !this.state.latitude) {
            return <div>Error: {this.state.errorMessage}</div>
        }
        if (!this.state.errorMessage && this.state.latitude) {
            // return <div>Latitude: {this.state.latitude}</div>
            return <SeasonDisplay lat={this.state.latitude}/>
        }
        
        return <Spinner message="Please accept location request"/>;
        // return <Spinner />;
        // return (
        //     <div>
        //         {/* <SeasonDisplay/> */}
        //         Latitude: {this.state.latitude}
        //         <br/>
        //         Error: {this.state.errorMessage}
        //     </div>
        // );
    };

    // React says we have to define render()!!!
    render() {
        console.log('render start')
        return (
            <div className="border red">
                {this.renderContent()}
            </div>
        );
    };
}

  
ReactDOM.render(
    <App />, 
    document.querySelector('#root')
);
  
