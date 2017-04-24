# Contributing to Falltergeist

Thank you for considering contributing to Falltergeist.

Following these guidelines helps to communicate that you respect the time of the developers managing and developing this open source project. In return, they should reciprocate that respect in addressing your issue, assessing changes, and helping you finalize your pull requests.

## Falltergeist needs you!

Currently the project needs following help:
- Experienced C++ developers for helping maintain good and stable code base
- Less experienced but eager to learn coders to implement game logic, UI and features
- People using various operating systems (Linux, Mac, Windows) and hardware to ensure project cross-platform capability


## Creating issues

Creating quality issues are a good way to help the development of the project.

### Bug Reports

When you find some bug, please add the following information to your issue:
- Meaningful title
- Clear and short summary of the issue, describing the core problem
- Description of your system that you used to build and run the game: 
    - Operating system
    - Compiler name and version
    - Build Profile (Debug, Release, etc.)
- A screenshot or a video, showing the issue - if there is something that can be shown (you can upload screenshots or captured video to any free file hosting and paste a link, or better add a proper [image in markdown](https://guides.github.com/features/mastering-markdown/) ).
- Steps to reproduce the issue (if possible)
- Additional notes, links, etc. (if any)

### Suggestions

When creating a suggestion or a feature request, please add:
- Meaningful title
- Clear short description, describing what you want and how do you think this change will help the project
- Additional information (if any)


## Contributing code

### Code Style

Please follow existing code style of the project described in our wiki (https://github.com/falltergeist/falltergeist/wiki/Code-style)

Using consistent code style helps to make code more fun to read and to write.

### Tell other devs what you are working on

When you start working on a fix/enhancement for an open issue please always post a comment in this issue's discussion to tell other devs that you have started working on it so that they won't waste any of their free time by working on their own fix/enhancement for it.

Alternatively, you can use Freenode or Jabber chat to inform the team of your plans.

If there isn't an open issue discussion for a bug fix/enhancement you want to work on please check that there isn't a closed discussion for it because a previous developer of it didn't finish their work which you could finish.

And if there is no existing issue discussion for what you want to work on please open a new issue for it and tell other devs here that your going to/ have started working on it.


### Getting Started Guide

#### First Time
1. Ensure you have a GitHub account (https://github.com/signup/free)
1. Fork falltergeist/falltergeist (https://github.com/falltergeist/falltergeist/fork)
1. Ensure you have a git client.  (http://desktop.github.com)
1. Clone your fork to your computer
    - If using github client, run Git Shell
    - `git clone https://github.com/falltergeist/falltergeist.git`
1. Add upstream remote
    - `git remote add upstream https://github.com/falltergeist/falltergeist.git`

#### Every Time
1. Sync your master branch with the Falltergeist repository's master branch
    - `git fetch upstream`
    - `git rebase upstream/master`
1. Make sure no one is already working on the issue you want to work on.
1. Tell other developers that you've started/will start working on this issue by posting a comment in its existing issue discussion or if there's no existing discussion for it then please open a new issue discussion for it and tell other
devs here that your working on it.
1. Create feature branch
    - `git branch myfeature upstream/master`
1. Checkout your feature branch
    - `git checkout myfeature`
1. Make your changes
1. Review your changes
	- `git diff`
	- git add (each file)
	- `git diff --check`
	- Check there's no white spaces.
	- `git commit`
	- Write an informative commit message and save
1. Push your changes to your fork
	- `git push origin myfeature`
1. Create a pull request
(https://github.com/mygithubuser/falltergeist/compare/falltergeist:master...myfeature)

Now watch to see if your feature is accepted.

#### Multiple commits
If your feature is very big, break it into subprojects and do a separate commit for every independent operation.  This means doing step 10 several times as you go.  You still only need to do one pull request at the end.

#### Syncing with Upstream:
If it takes a long time between when you start your feature and when you finish there might be other important changes other people are making to Falltergeist. It is a good idea to make sure your code will still operate correctly with the latest changes. To do this:
        - git fetch upstream
        - git rebase upstream/master
What this does is downloads all the changes from falltergeist\falltergeist since you started, and pretends that all your changes were made after them. If there are conflicts, for example if someone else changed the same line in the same file that you did you will be asked to resolve those conflicts.

If you follow these guidelines then you should be well on your way to producing good pull requests.


### Pull Requests

When providing a pull request ensure the description field describes the major changes from the request. If your pull request relates to any existing issues, include those issues in the description. e.g. "Fixes #1"


# Contacts

If you need more help just ask the friendly people on falltergeist channel on jabber.ru (English and Russian)
