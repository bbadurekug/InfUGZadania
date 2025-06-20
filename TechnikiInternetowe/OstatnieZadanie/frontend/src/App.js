import 'bootstrap/dist/css/bootstrap.min.css';

import logo from './logo.svg';
import './App.css';

import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';

import Home from './pages/Home';
import LoginPage from './pages/Login';
import RegisterPage from './pages/Register';
import Match from './pages/Match';
import Admin from './pages/Admin';
import AdminUsers from './pages/AdminUsers';
import AdminPlayers from './pages/AdminPlayers';
import AdminTeams from './pages/AdminTeams';
import AdminMatches from './pages/AdminMatches';
import AdminComments from './pages/AdminComments';

function App() {
  
	return (
		<Router>
			<Routes>
				<Route path="/" element={<Home />} />
				<Route path="/login" element={<LoginPage />} />
				<Route path="/register" element={<RegisterPage />} />
				<Route path="/matches/:id" element={<Match />} />
				<Route path="/admin" element={<Admin />} />
				<Route path="/admin/users" element={<AdminUsers />} />
				<Route path="/admin/players" element={<AdminPlayers />} />
				<Route path="/admin/teams" element={<AdminTeams />} />
				<Route path="/admin/matches" element={<AdminMatches />} />
				<Route path="/admin/comments" element={<AdminComments />} />
			</Routes>
		</Router>
	);
}

export default App;
