import React, { Component } from 'react';
import LanguageContext from '../contexts/LanguageContext';
import ColorContext from '../contexts/ColorContext';

class Button extends Component {
    // static contextType = LanguageContext;

    renderSubmit(language) {
        return  language === 'english' ? 'Submit' : 'Voorleggen'
    }

    renderButton(color) {
        return (
            <button className={`ui button ${color}`}>
                <LanguageContext.Consumer>
                    {({ language }) => this.renderSubmit(language)}                
                </LanguageContext.Consumer>
            </button>
        );
    }

    render() {
        // console.log(this.context);
        // const text = this.context === 'english' 
        //     ? 'Submit' 
        //     : 'Voorleggen';


        return (
            <ColorContext.Consumer>
                {(color) => this.renderButton(color)}                
            </ColorContext.Consumer>
            
            // <button className="ui button primary">
            //     {text}
            // </button>
        )
    }
}

export default Button;