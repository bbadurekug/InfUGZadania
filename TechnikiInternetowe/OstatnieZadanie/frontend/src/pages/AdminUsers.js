import React, { useEffect, useState } from 'react';
import { Container, Button, ListGroup, Row, Col, Form } from 'react-bootstrap';

function AdminUsers() {
	
	const [users, setUsers] = useState([]);
	const [form, setForm] = useState({ name: '', password: '', role: 'USER' });
	const [editingUser, setEditingUser] = useState(null);
	
	const user = JSON.parse(localStorage.getItem('user'));

	useEffect(() => {
		fetch('/admin/users')
			.then(res => res.json())
			.then(data => setUsers(data));
	}, []);

	if (!user || user.role !== 'ADMIN') {
		return <p>Brak dostępu do sesji administratora.</p>;
	}

	async function handleCreate(e) {
		e.preventDefault();
		const res = await fetch('/admin/users', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),
		});
		const newUser = await res.json();
		setUsers([...users, newUser]);
		setForm({ name: '', password: '', role: 'USER'});
	}

	async function handleDelete(id) {
		await fetch(`/admin/users/${id}`, { method: 'DELETE' });
		setUsers(users.filter(u => u.id !== id));
	
	}

	function startEditing(user) {
		setEditingUser(user);
		setForm({ name: user.name, password: '', role: user.role });
	}

	async function handleUpdate(e) {
		e.preventDefault();
		const res = await fetch(`/admin/users/${editingUser.id}`, {
			method: 'PUT',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),

		});

		if (res.ok) {
			const updated = await res.json();
			setUsers(users.map(u => u.id === updated.id ? updated : u));
			setEditingUser(null);
			setForm({ name: '', password: '', role: 'USER' });
		}
		else {
			alert('Błąd aktualizacji');
		}
	}
	

	return (
		<div
			style={{
				backgroundImage: 'url(/img/admin.jpg)',
               			backgroundSize: 'cover',
               			backgroundPosition: 'center',
               			minHeight: '100vh',
               			padding: '20px',
			}}
		>
			<Container className="my-4">
				<h1 className="mb-4 text-center text-white">Panel administratora</h1>
				
				<Form onSubmit={editingUser ? handleUpdate : handleCreate}>
					<Row className="mb-3">
						<Form.Group as={Col} controlId="formName">
							<Form.Label className="text-white">Name</Form.Label>
							<Form.Control
								type="text"
								placeholder="Name"
								value={form.name}
								onChange={e => setForm({ ...form, name: e.target.value })}
								required
							/>
						</Form.Group>
						<Form.Group as={Col} controlId="formPassword">
							<Form.Label className="text-white">Password</Form.Label>
							<Form.Control
								type="text"
								placeholder="Password"
								value={form.password}
								onChange={e => setForm({ ...form, password: e.target.value })}
								required
							/>
						</Form.Group>
						<Form.Group as={Col} controlId="formRole">
							<Form.Label className="text-white">Role</Form.Label>
							<Form.Select
								value={form.role}
								onChange={e => setForm({ ...form, role: e.target.value })}
								required
							>
								<option value="USER">USER</option>
								<option value="ADMIN">ADMIN</option>
							</Form.Select>
						</Form.Group>
					</Row>
					<div className="d-flex gap-2 mb-3">
						<Button type="submit" variant={editingUser ? 'success' : 'primary'}>
							{editingUser ? 'Update' : 'Create'}
						</Button>
						{editingUser && <Button variant="secondary" type="button" onClick={() => {
							setEditingUser(null);
							setForm({ name: '', password: '', role: 'USER' });
						}}>Cancel</Button>}
					</div>
				</Form>

				<ListGroup>
					{users.map(u => (
						<ListGroup.Item key={u.id} className="d-flex justify-content-between align-itams-center">
							<div>
								{u.name} ({u.role})
							</div>
							<div className="d-flex gap-2">
								<Button variant="warning" onClick={() => startEditing(u)}>
									Edit
								</Button>
								<Button variant="danger" onClick={() => handleDelete(u.id)}>
									Delete
								</Button>
							</div>
						</ListGroup.Item>
					))}
				</ListGroup>	

			</Container>
		</div>	
	)
		
}

export default AdminUsers;	
