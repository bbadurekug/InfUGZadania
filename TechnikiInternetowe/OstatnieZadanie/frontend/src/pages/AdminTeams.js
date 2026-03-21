import React, { useEffect, useState } from 'react';
import { Container, Button, ListGroup, Row, Col, Form } from 'react-bootstrap';

function AdminTeams() {

	const [teams, setTeams] = useState([]);
	const [form, setForm] = useState({ name: '', shortName: '' });
	
	const [editingTeam, setEditingTeam] = useState(null);

	const user = JSON.parse(localStorage.getItem('user'));

	useEffect(() => {
		fetch('/admin/teams')
			.then(res => res.json())
			.then(data => setTeams(data));
	}, []);

	if (!user || user.role !== 'ADMIN') {
		return <p>Brak dostępu do sesji administratora.</p>;
	}

	async function handleCreate(e) {
		e.preventDefault();
		const res = await fetch('/admin/teams', {
			method: 'POST',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),
		});
		const newTeam = await res.json();
		setTeams([...teams, newTeam]);
		setForm({ name: '', shortName: '' });
	}

	async function handleDelete(id) {
		await fetch(`/admin/teams/${id}`, { method: 'DELETE' });
		setTeams(teams.filter(u => u.id !== id));
	}

	function startEditing(team) {
		setEditingTeam(team);
		setForm({ name: team.name, shortName: team.shortName});
	}

	async function handleUpdate(e) {
		e.preventDefault();
		const res = await fetch(`/admin/teams/${editingTeam.id}`, {
			method: 'PUT',
			headers: { 'Content-Type': 'application/json' },
			body: JSON.stringify(form),

		});

		if (res.ok) {
			const updated = await res.json();
			setTeams(teams.map(u => u.id === updated.id ? updated : u));
			setEditingTeam(null);
			setForm({ name: '', shortName: '' });
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
				
				<Form onSubmit={editingTeam ? handleUpdate : handleCreate}>
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
						<Form.Group as={Col} controlId="formShortName">
							<Form.Label className="text-white">ShortName</Form.Label>
							<Form.Control
								type="text"
								placeholder="ShortName"
								value={form.shortName}
								onChange={e => setForm({ ...form, shortName: e.target.value })}
								required
							/>
						</Form.Group>
					</Row>
					<div className="d-flex gap-2 mb-3">
						<Button type="submit" variant={editingTeam ? 'success' : 'primary'}>
							{editingTeam ? 'Update' : 'Create'}
						</Button>
						{editingTeam && <Button variant="secondary" type="button" onClick={() => {
							setEditingTeam(null);
							setForm({ name: '', shortName: '' });
						}}>Cancel</Button>}
					</div>
				</Form>

				<ListGroup>
					{teams.map(u => (
						<ListGroup.Item key={u.id} className="d-flex justify-content-between align-itams-center">
							<div>	
								{u.name} {u.shortName}
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

export default AdminTeams;	
