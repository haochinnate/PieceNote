import React, { Component } from 'react';
import UserCreate from './UserCreate';
import { LanguageStore } from '../contexts/LanguageContext';
import ColorContext from '../contexts/ColorContext';
import LanguageSelector from './LanguageSelector';

class App extends Component {

    render() {
        return (
            <div className="ui container">

                <LanguageStore>
                    <LanguageSelector/>
                    <ColorContext.Provider value="red">
                        <UserCreate />
                    </ColorContext.Provider>
                </LanguageStore>

                {/* {this.state.language} */}
                {/* <LanguageContext.Provider value={this.state.language}>
                    <ColorContext.Provider value="red">
                        <UserCreate />
                    </ColorContext.Provider>
                </LanguageContext.Provider> */}

                {/* <LanguageContext.Provider value="english">
                    <UserCreate />
                </LanguageContext.Provider> */}
            </div>
        )
    }
}

export default App;
