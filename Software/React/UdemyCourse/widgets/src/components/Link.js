import React from 'react';

const Link = ({ className, href, children }) => {
    
    const onClick = (event) => {

        // open in new tab
        if (event.metaKey || event.ctrlKey) {
            return;
        }

        // prevent default action (will refrech all content)
        event.preventDefault();

        // update URL
        window.history.pushState({}, '', href);

        // navigation event, told other components URL had changed
        const navEvent = new PopStateEvent('popstate');
        window.dispatchEvent(navEvent);
    };
    
    return (
        <a onClick={onClick} className={className} href={href}>
            {children}
        </a>
    )
};

export default Link;
