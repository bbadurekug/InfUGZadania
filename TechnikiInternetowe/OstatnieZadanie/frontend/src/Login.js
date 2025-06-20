import React, { useState } from 'react';
import { Container, Form, Button, Alert } from 'react-bootstrap';

function Login() {
	const [name, setName] = useState('');
	const [password, setPassword] = useState('');
	const [message, setMessage] = useState('');

	async function handleSubmit(e) {
		e.preventDefault();

		const res = await fetch('/login', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify({ name, password }),
		});

		const data = await res.json();

		if (res.ok) {
			localStorage.setItem('user', JSON.stringify(data));

			if (data.role === 'ADMIN') {
				window.location.href = '/admin';
			}
			else {
				window.location.href = '/';
			}
		}
		else {
			setMessage(data.error || 'Nieudany login');
		}
	
	}

	return (
		<div
			style={{
				backgroundImage: 'url(/img/login.jpg)',
               			backgroundSize: 'cover',
               			backgroundPosition: 'center',
               			minHeight: '100vh',
               			padding: '20px',
			}}
		>
			<Container className="my-4" style={{ maxWidth: '20%' }}>
				<h2 className="text-center mb-4 text-white">Login</h2>
				<Form onSubmit={handleSubmit}>
					<Form.Group controlId="formUserName" className="mb-3"> 
						<Form.Label className="text-white">Username:</Form.Label>
						<Form.Control
							type="text"
							value={name}
							onChange={(e) => setName(e.target.value)}
							required
						/>
					</Form.Group>
					<Form.Group controlId="formPassword" className="mb-3">
						<Form.Label className="text-white">Password:</Form.Label>
						<Form.Control
							type="password"
							value={password}
							onChange={(e) => setPassword(e.target.value)}
							required
						/>
					</Form.Group>
					<div className="d-flex justify-content-center">
						<Button type="submit" variant="primary" className="w-20">
							Login
						</Button>
					</div>
				</Form>
				{message && <Alert variant="danger" className="mt-3">{message}</Alert>}
			</Container>
		</div>
	);
}

export default Login;
