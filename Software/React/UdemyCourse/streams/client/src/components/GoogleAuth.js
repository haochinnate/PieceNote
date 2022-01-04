import React, { Component } from 'react'
import { connect } from 'react-redux';
import { signIn, signOut } from '../actions'

class GoogleAuth extends Component {

    // state = { isSignedIn: null };

    componentDidMount() {
        window.gapi.load('client:auth2', () => {
            // console.log('finished callback')
            // initialized
            window.gapi.client.init({
                clientId: '355212624893-djd29qqfj16ojac51geg6vmdi6gqell0.apps.googleusercontent.com',
                scope: 'email'
            }).then(() => {
                // get reference of 'auth' object
                this.auth = window.gapi.auth2.getAuthInstance();

                // 查看 user 有沒有 signed in 
                // this.setState({ isSignedIn: this.auth.isSignedIn.get() })
                this.onAuthChange(this.auth.isSignedIn.get());

                // 監聽 isSignedIn, 有變化的時候執行其他 code
                this.auth.isSignedIn.listen(this.onAuthChange);
            });

        });
    }

    onAuthChange = (isSignedIn) => {
        // this.setState({ isSignedIn: this.auth.isSignedIn.get() });
        if (isSignedIn) {
            this.props.signIn(this.auth.currentUser.get().getId());
        } else {
            this.props.signOut();
        }
    };

    onSignInClick = () => {
        this.auth.signIn();
    };

    onSignOutClick = () => {
        this.auth.signOut();
    };

    renderAuthButton() {
        if (this.props.isSignedIn === null) {
            // return <div>I don't know if we are signed in</div>
            return null;
        } else if (this.props.isSignedIn) {
            return (
                // <div>I am signed in!</div>
                <button className="ui red google button"
                    onClick={this.onSignOutClick}>
                    <i className="google icon"/>
                    Sign Out
                </button>
            );
        } else {
            return (
                // <div>I am not signed in</div>
                <button className="ui red google button"
                    onClick={this.onSignInClick}>
                    <i className="google icon"/>
                    Sign In with Google
                </button>
            );
        }

    }

    render() {
        return (
            <div>
                {/* 印出 authentication status */}
                {this.renderAuthButton()}
            </div>
        )
    }
}

const mapStateToProps = (state) => {
    return { isSignedIn: state.auth.isSignedIn }
};

export default connect(
    mapStateToProps, 
    { signIn, signOut }
)(GoogleAuth);
